#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";


const char* squareFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0, 0.0, 0.1, 1.0); // orange color\n"
"}\n\0";

const char* triangleFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0, 0.84, 0.0, 1.0); // gold color\n"
"}\n\0";

const char* triangle2FragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0, 0.2, 0.2, 1.0); // Blue color\n"
"}\n\0";

const char* cmniFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(.8, .8, .8, 1.0); // Blue color\n"
"}\n\0";


const char* circleFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0, 1.0, 1.0, 1.0); // Blue color\n"
"}\n\0";

const char* windowFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Blue color\n"
"}\n\0";

const char* win1FragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.376, 0.376, 0.376, 1.0); // Blue color\n"
"}\n\0";

const char* glassFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.6, 0.8, 1.0, 1.0); // Blue color\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Example", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Compile and link the shaders for the square
    unsigned int squareVertexShader, squareFragmentShader, squareShaderProgram;
    squareVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(squareVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(squareVertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(squareVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(squareVertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    squareFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(squareFragmentShader, 1, &squareFragmentShaderSource, NULL);
    glCompileShader(squareFragmentShader);

    glGetShaderiv(squareFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(squareFragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    squareShaderProgram = glCreateProgram();
    glAttachShader(squareShaderProgram, squareVertexShader);
    glAttachShader(squareShaderProgram, squareFragmentShader);
    glLinkProgram(squareShaderProgram);
    glDeleteShader(squareVertexShader);
    glDeleteShader(squareFragmentShader);

    glGetProgramiv(squareShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(squareShaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }

    // Define vertices for the square
    float squareVertices[] = {
     -0.859342358f, 	0.176172147f, 0.0f,
    -0.6747909f,  -0.847289924f, 0.0f,
     0.9622931f, -0.062814224f, 0.0f,
     0.915678877f, -0.825702676f, 0.0f
    };


    // Create VAO and VBO for the square
    unsigned int squareVAO, squareVBO;
    glGenVertexArrays(1, &squareVAO);
    glGenBuffers(1, &squareVBO);

    glBindVertexArray(squareVAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //window fragment

    unsigned int windowVertexShader, windowFragmentShader, windowShaderProgram;
    windowVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(windowVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(windowVertexShader);

    glGetShaderiv(windowVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(windowVertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    windowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(windowFragmentShader, 1, &windowFragmentShaderSource, NULL);
    glCompileShader(windowFragmentShader);

    glGetShaderiv(windowFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(windowFragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    windowShaderProgram = glCreateProgram();
    glAttachShader(windowShaderProgram, windowVertexShader);
    glAttachShader(windowShaderProgram, windowFragmentShader);
    glLinkProgram(windowShaderProgram);
    glDeleteShader(windowVertexShader);
    glDeleteShader(windowFragmentShader);

    glGetProgramiv(windowShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(windowShaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }
    


    //window
        // Define vertices for the square
    float squareWindowVertices[] = {
     0.453867875f, 	0.262115566f, 0.0f,
    0.45005701f,  0.112083808f, 0.0f,
    0.532690792f, 0.100272423f, 0.0f,
   // 0.543859381f, 0.262865495f, 0.0f
    };


    // Create VAO and VBO for the square
    unsigned int squareWindowVAO, squareWindowVBO;
    glGenVertexArrays(1, &squareWindowVAO);
    glGenBuffers(1, &squareWindowVBO);

    glBindVertexArray(squareWindowVAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindowVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindowVertices), squareWindowVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow1Vertices[] = {
    
   // 0.45005701f,  0.112083808f, 0.0f,
    0.532690792f, 0.100272423f, 0.0f,
    0.532690792f, 0.242115566f, 0.0f,
     0.453867875f, 	0.262115566f, 0.0f,
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow1VAO, squareWindow1VBO;
    glGenVertexArrays(1, &squareWindow1VAO);
    glGenBuffers(1, &squareWindow1VBO);

    glBindVertexArray(squareWindow1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow1Vertices), squareWindow1Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Define vertices for the square
    float squareWindow2Vertices[] = {
     0.553867875f, 	0.242115566f, 0.0f,
    0.55005701f,  0.102083808f, 0.0f,
    0.632690792f, 0.09300272423f, 0.0f,
   // 0.543859381f, 0.262865495f, 0.0f
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow2VAO, squareWindow2VBO;
    glGenVertexArrays(1, &squareWindow2VAO);
    glGenBuffers(1, &squareWindow2VBO);

    glBindVertexArray(squareWindow2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow2Vertices), squareWindow2Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow3Vertices[] = {
    0.632690792f, 0.09300272423f, 0.0f,
    0.632690792f, 0.222115566f, 0.0f,
    0.553867875f, 	0.242115566f, 0.0f
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow3VAO, squareWindow3VBO;
    glGenVertexArrays(1, &squareWindow3VAO);
    glGenBuffers(1, &squareWindow3VBO);

    glBindVertexArray(squareWindow3VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow3Vertices), squareWindow3Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow4Vertices[] = {
      0.653867875f, 	0.222115566f, 0.0f,
      0.653867875f, 0.09300272423f, 0.0f,
    0.732690792f, 0.08700272423f, 0.0f,
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow4VAO, squareWindow4VBO;
    glGenVertexArrays(1, &squareWindow4VAO);
    glGenBuffers(1, &squareWindow4VBO);

    glBindVertexArray(squareWindow4VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow4VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow4Vertices), squareWindow4Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow5Vertices[] = {
     0.732690792f, 0.08700272423f, 0.0f,
    0.732690792f, 0.202115566f, 0.0f,
    0.653867875f, 	0.222115566f, 0.0f
    
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow5VAO, squareWindow5VBO;
    glGenVertexArrays(1, &squareWindow5VAO);
    glGenBuffers(1, &squareWindow5VBO);

    glBindVertexArray(squareWindow5VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow5VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow5Vertices), squareWindow5Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow6Vertices[] = {
     0.753867875f, 	0.202115566f, 0.0f,
      0.753867875f, 0.09000272423f, 0.0f,
     0.832690792f, 0.08700272423f, 0.0f,
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow6VAO, squareWindow6VBO;
    glGenVertexArrays(1, &squareWindow6VAO);
    glGenBuffers(1, &squareWindow6VBO);

    glBindVertexArray(squareWindow6VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow6VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow6Vertices), squareWindow6Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float squareWindow7Vertices[] = {
     0.832690792f, 0.08700272423f, 0.0f,
    0.832690792f, 0.192115566f, 0.0f,
    0.753867875f, 	0.202115566f, 0.0f
    };


    // Create VAO and VBO for the square
    unsigned int squareWindow7VAO, squareWindow7VBO;
    glGenVertexArrays(1, &squareWindow7VAO);
    glGenBuffers(1, &squareWindow7VBO);

    glBindVertexArray(squareWindow7VAO);
    glBindBuffer(GL_ARRAY_BUFFER, squareWindow7VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareWindow7Vertices), squareWindow7Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the square
    float cimniupVertices[] = {
     0.807115145f, 0.948392626f, 0.0f,
     0.807115145f, 0.898392626f, 0.0f,
     0.870839997f, 	0.898392626f, 0.0f
    };

    // Create VAO and VBO for the square
    unsigned int cimniupVAO, cimniupVBO;
    glGenVertexArrays(1, &cimniupVAO);
    glGenBuffers(1, &cimniupVBO);

    glBindVertexArray(cimniupVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cimniupVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cimniupVertices), cimniupVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float cimniup1Vertices[] = {
 0.870839997f, 	0.898392626f, 0.0f,
 0.870839997f, 0.948392626f, 0.0f,
 0.807115145f, 0.948392626f, 0.0f
 
    };

    // Create VAO and VBO for the square
    unsigned int cimniup1VAO, cimniup1VBO;
    glGenVertexArrays(1, &cimniup1VAO);
    glGenBuffers(1, &cimniup1VBO);

    glBindVertexArray(cimniup1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cimniup1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cimniup1Vertices), cimniup1Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
   

    // Define vertices for the square
    float lineVertices[] = {
     -0.859342358f, 	0.176172147f, 0.0f,
    - 0.859342358f, 	0.376172147f, 0.0f
    };


    // Create VAO and VBO for the square
     unsigned int lineVAO, lineVBO;
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    


    // Compile and link the shaders for the triangle
    unsigned int triangleVertexShader, triangleFragmentShader, triangleShaderProgram;
    triangleVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangleVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(triangleVertexShader);

    glGetShaderiv(triangleVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(triangleVertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    triangleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(triangleFragmentShader, 1, &triangleFragmentShaderSource, NULL);
    glCompileShader(triangleFragmentShader);

    glGetShaderiv(triangleFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(triangleFragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    triangleShaderProgram = glCreateProgram();
    glAttachShader(triangleShaderProgram, triangleVertexShader);
    glAttachShader(triangleShaderProgram, triangleFragmentShader);
    glLinkProgram(triangleShaderProgram);
    glDeleteShader(triangleVertexShader);
    glDeleteShader(triangleFragmentShader);

    glGetProgramiv(triangleShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(triangleShaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }

    // Define vertices for the triangle
    float triangleVertices[] = {
    -0.425500654f,0.629787495f, 0.0f, // right
      -0.427804008f, 0.121434967f, 0.0f, // left
       0.914550157f, -0.054878749f, 0.0f  // top
    };

    // Create VAO and VBO for the triangle
    unsigned int triangleVAO, triangleVBO;
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Define vertices for the triangle3
    float triangle3Vertices[] = {
      0.914550157f, -0.054878749f, 0.0f,
     0.914905991f, 0.332624217f, 0.0f,  // top
      - 0.425500654f,0.629787495f, 0.0f
    };


    // Create VAO and VBO for the triangle3
    unsigned int triangle3VAO, triangle3VBO;
    glGenVertexArrays(1, &triangle3VAO);
    glGenBuffers(1, &triangle3VBO);

    glBindVertexArray(triangle3VAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangle3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3Vertices), triangle3Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Compile and link the shaders for the triangle2
    unsigned int triangle2VertexShader, triangle2FragmentShader, triangle2ShaderProgram;
    triangle2VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangle2VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(triangle2VertexShader);

    glGetShaderiv(triangle2VertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(triangle2VertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    triangle2FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(triangle2FragmentShader, 1, &triangle2FragmentShaderSource, NULL);
    glCompileShader(triangle2FragmentShader);

    glGetShaderiv(triangle2FragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(triangle2FragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    triangle2ShaderProgram = glCreateProgram();
    glAttachShader(triangle2ShaderProgram, triangle2VertexShader);
    glAttachShader(triangle2ShaderProgram, triangle2FragmentShader);
    glLinkProgram(triangle2ShaderProgram);
    glDeleteShader(triangle2VertexShader);
    glDeleteShader(triangle2FragmentShader);

    glGetProgramiv(triangle2ShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(triangle2ShaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }

    // Define vertices for the triangle2
    float triangle2Vertices[] = {
         -0.715003941f,-0.6392917f, 0.0f, // right
          -0.696737808f, -0.747472815f, 0.0f,
         0.921272737f, -0.733989394f, 0.0f
    };

    // Create VAO and VBO for the triangle2
    unsigned int triangle2VAO, triangle2VBO;
    glGenVertexArrays(1, &triangle2VAO);
    glGenBuffers(1, &triangle2VBO);

    glBindVertexArray(triangle2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangle2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2Vertices), triangle2Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Define vertices for the triangle4
    float triangle4Vertices[] = {
        -0.715003941f,-0.6392917f, 0.0f, // right
     0.921272737f, -0.733989394f, 0.0f, // left
     0.926878075f,-0.629776016f, 0.0f,
    };


    // Create VAO and VBO for the triangle4
    unsigned int triangle4VAO, triangle4VBO;
    glGenVertexArrays(1, &triangle4VAO);
    glGenBuffers(1, &triangle4VBO);

    glBindVertexArray(triangle4VAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangle4VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4Vertices), triangle4Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float cimniup2Vertices[] = {
     0.645375309f, 0.813711461f, 0.0f,
     0.645375309f, 0.763711461f, 0.0f,
     0.711093596f, 0.763711461f, 0.0f

    };

    // Create VAO and VBO for the square
    unsigned int cimniup2VAO, cimniup2VBO;
    glGenVertexArrays(1, &cimniup2VAO);
    glGenBuffers(1, &cimniup2VBO);

    glBindVertexArray(cimniup2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cimniup2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cimniup2Vertices), cimniup2Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float cimniup3Vertices[] = {
      0.711093596f, 0.763711461f, 0.0f,
      0.711495344f,0.818429128f, 0.0f,
     0.645375309f, 0.813711461f, 0.0f

    };

    // Create VAO and VBO for the square
    unsigned int cimniup3VAO, cimniup3VBO;
    glGenVertexArrays(1, &cimniup3VAO);
    glGenBuffers(1, &cimniup3VBO);

    glBindVertexArray(cimniup3VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cimniup3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cimniup3Vertices), cimniup3Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Compile and link the shaders for the cmni
    unsigned int cmniVertexShader, cmniFragmentShader, cmniShaderProgram;
    cmniVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(cmniVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(cmniVertexShader);

    glGetShaderiv(cmniVertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(cmniVertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    cmniFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(cmniFragmentShader, 1, &cmniFragmentShaderSource, NULL);
    glCompileShader(cmniFragmentShader);

    glGetShaderiv(cmniFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(cmniFragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        return -1;
    }

    cmniShaderProgram = glCreateProgram();
    glAttachShader(cmniShaderProgram, cmniVertexShader);
    glAttachShader(cmniShaderProgram, cmniFragmentShader);
    glLinkProgram(cmniShaderProgram);
    glDeleteShader(cmniVertexShader);
    glDeleteShader(cmniFragmentShader);

    glGetProgramiv(cmniShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(cmniShaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        return -1;
    }

    // Define vertices for the cmni
    float cmniVertices[] = {
      0.807115145f, 0.948392626f, 0.0f,
        0.804739094f, 0.360872826f, 0.0f,
        0.870839997f, 0.344757f, 0.0f
    };

    // Create VAO and VBO for the cmni
    unsigned int cmniVAO, cmniVBO;
    glGenVertexArrays(1, &cmniVAO);
    glGenBuffers(1, &cmniVBO);

    glBindVertexArray(cmniVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cmniVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cmniVertices), cmniVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Define vertices for the cmni2
    float cmni2Vertices[] = {
     0.870839997f, 0.344757f, 0.0f,
     0.870839997f,0.94892829f, 0.0f,
     0.807115145f, 0.948392626f, 0.0f
    };

    // Create VAO and VBO for the cmni2
    unsigned int cmni2VAO, cmni2VBO;
    glGenVertexArrays(1, &cmni2VAO);
    glGenBuffers(1, &cmni2VBO);

    glBindVertexArray(cmni2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cmni2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cmni2Vertices), cmni2Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);




    // Define vertices for the cmni3
    float cmni3Vertices[] = {
     0.645375309f, 0.813711461f, 0.0f,
     0.644988866f, 0.392874907f, 0.0f,
     0.711093596f, 0.38092578f, 0.0f
    };

    // Create VAO and VBO for the cmni3
    unsigned int cmni3VAO, cmni3VBO;
    glGenVertexArrays(1, &cmni3VAO);
    glGenBuffers(1, &cmni3VBO);

    glBindVertexArray(cmni3VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cmni3VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cmni3Vertices), cmni3Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Define vertices for the cmni4

    float cmni4Vertices[] = {
      0.711093596f, 0.38092578f, 0.0f,
      0.711495344f,0.818429128f, 0.0f,
     0.645375309f, 0.813711461f, 0.0f
     
    };

    // Create VAO and VBO for the cmni4
    unsigned int cmni4VAO, cmni4VBO;
    glGenVertexArrays(1, &cmni4VAO);
    glGenBuffers(1, &cmni4VBO);

    glBindVertexArray(cmni4VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cmni4VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cmni4Vertices), cmni4Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the square
        glUseProgram(squareShaderProgram);
        glBindVertexArray(squareVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Draw the square
       // glUseProgram(UpperVertexShader);
       // glBindVertexArray(UpperVAO);
       // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Draw the triangle
        glUseProgram(triangleShaderProgram);
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the triangle
        glUseProgram(triangle2ShaderProgram);
        glBindVertexArray(triangle2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // Draw the triangle
        glUseProgram(triangleShaderProgram);
        glBindVertexArray(triangle3VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the triangle
       glUseProgram(triangle2ShaderProgram);
        glBindVertexArray(triangle4VAO);
       glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cmni1
        glUseProgram(windowShaderProgram);
        glBindVertexArray(cmniVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cmni2
        glUseProgram(windowShaderProgram);
        glBindVertexArray(cmni2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cmni3
        glUseProgram(windowShaderProgram);
        glBindVertexArray(cmni3VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cmni4
        glUseProgram(windowShaderProgram);
        glBindVertexArray(cmni4VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindowVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow3VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow4VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow5VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow6VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
        glUseProgram(windowShaderProgram);
        glBindVertexArray(squareWindow7VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cimniup
        glUseProgram(cmniShaderProgram);
        glBindVertexArray(cimniupVAO);  // Draw the window
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cimniup1
        glUseProgram(cmniShaderProgram);
        glBindVertexArray(cimniup1VAO);  // Draw the window
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the cimniup1
        glUseProgram(cmniShaderProgram);
        glBindVertexArray(cimniup2VAO);  // Draw the window
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(cmniShaderProgram);
        glBindVertexArray(cimniup3VAO);  // Draw the window
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw the window
       glUseProgram(triangle2ShaderProgram);
        glBindVertexArray(lineVAO);
        glDrawArrays(GL_LINE, 0, 2);

        /*
        // Draw the cmni4
        glUseProgram(circleShaderProgram);
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 25);
        */

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and exit
    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1, &squareVBO);
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
} 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define DEBUG

#ifdef _WIN32
    #define alloca __builtin_alloca 
#endif

static unsigned int CompileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);
    //const char* src = &source[0];
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE)
    {
        int length; 
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        
        return 0;
    }
        
    
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
       -0.5f, -0.5f, // 0
        0.0f,  0.5f, // 2
        0.5f, -0.5f, // 1
    };

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader = 
            "#version 300 es\n"
            "\n"
            "layout(location = 0) in vec4 position;\n"
            "\n"
            "void main()\n"
            "{\n"
            " gl_Position = position;\n"
            "}\n";
    
    std::string fragmentShader = 
            "#version 300 es\n"
            "\n"
            "layout(location = 0) out mediump vec4 color;\n"
            "\n"
            "void main()\n"
            "{\n"
            " color = vec4(0.0, 1.0, 0.0, 1.0);\n"
            "}\n";
   
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
 
        glDrawArrays(GL_TRIANGLES, 0, 3);
         
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
 
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();

    return 0;
}
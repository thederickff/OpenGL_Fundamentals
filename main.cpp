#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define DEBUG

#ifdef _WIN32
    #define alloca __builtin_alloca 
#endif

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    GLCall(glfwMakeContextCurrent(window));

    GLCall(glfwSwapInterval(1));

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Create a scope to destroy VertexBuffer and IndexBuffer objects before glfwTerminate()
    {
        // float positions[] = {
        //    -0.5f, -0.5f, 0.0f, 0.0f, // 0
        //     0.5f, -0.5f, 1.0f, 0.0f, // 1
        //     0.5f,  0.5f, 1.0f, 1.0f, // 2
        //    -0.5f,  0.5f, 0.0f, 1.0f// 3
        // };

        float positions[] = {
            -0.75f,   0.0f, // 0
            -0.25f,  0.5f, // 1
             0.25f,  0.5f, // 2
             0.75f,   0.0f, // 3
             0.25f, -0.5f, // 4
            -0.25f, -0.5f, // 5
        };

        unsigned int indices[] = {
            0, 1, 5,
            1, 5, 2,
            4, 5, 2,
            2, 4, 3
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;

        VertexBuffer vb(positions, 2 * 6 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        // layout.Push<float>(2);

        va.AddBuffer(vb, layout);
        
        IndexBuffer ib(indices, 4 * 3);

        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        // Texture texture("res/textures/cherno.jpg");
        // texture.Bind();
        // shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float inc = 0.02f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
    
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.8f, 0.0f, 1.0f);
        
            renderer.Draw(va, ib, shader);
            
            if (r > 1.0f)
                inc = -0.02f;
            else if (r < 0.0f)
                inc = 0.02f;

            r += inc;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));
    
            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }
    GLCall(glfwTerminate());

    return 0;
}
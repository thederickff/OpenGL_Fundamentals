/* 
 * File:   main.cpp
 * Author: derickfelix
 *
 * Created on December 20, 2017, 7:42 PM
 */
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
#include "Shader.h"

int main(int argc, char** argv) {

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    
    /* Initialize the library GLEW */
    if (glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
       -0.5f, -0.5f, // 0
        0.5f, -0.5f, // 1
        0.5f,  0.5f, // 2
       -0.5f,  0.5f, // 3
    };
    
    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };
    
    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    // Set the layout of our vertex buffer, enable index 0 which is linked to vertex array object
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);


    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.5f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

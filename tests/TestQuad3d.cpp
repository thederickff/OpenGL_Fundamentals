#include "TestQuad3d.h"
#include "VertexBufferLayout.h"

#include "glm/gtx/transform.hpp"

namespace test {
  
  TestQuad3d::TestQuad3d(GLFWwindow *window)
  : m_window(window), m_shader("res/shaders/testQuad3d.shader"),
    m_color{1, 0, 1, 1}, m_fov(90.0f), m_velocity(2.5f), m_mouseSensitivity(0.10f),
    m_cameraPos{0.0f, 0.0f, 3.0f}, m_cameraFront{0.0f, 0.0f, -1.0f}, m_cameraUp{0.0f, 1.0f, 0.0f},
    m_lastMouseX(0.0f), m_lastMouseY(0.0f), m_yaw(-90.0f), m_pitch(0.0f), m_yPos(0.0f)
  {
    float vertices[] = {
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,

      -0.5f, -0.5f, 0.5f,
       0.5f, -0.5f, 0.5f,
       0.5f,  0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,

      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, 0.5f,
      -0.5f, -0.5f, 0.5f,

      -0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,

      0.5f, -0.5f, -0.5f,
      0.5f, 0.5f, -0.5f,
      0.5f, 0.5f, 0.5f,
      0.5f, -0.5f, 0.5f,

      -0.5f, -0.5f, -0.5f,
      -0.5f, 0.5f, -0.5f,
      -0.5f, 0.5f, 0.5f,
      -0.5f, -0.5f, 0.5f
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0,
      4, 5, 6,
      6, 7, 4,
      8, 9, 10,
      10, 11, 8,
      12, 13, 14,
      14, 15, 12,
      16, 17, 18,
      18, 19, 16,
      20, 21, 22,
      22, 23, 20
    };

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_indexBuffer = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout layout;
    layout.Push<float>(3);

    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
  }

  TestQuad3d::~TestQuad3d()
  {
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
  }

  void TestQuad3d::onUpdate(int deltaTime)
  {
    onInputUpdate(deltaTime);
    onMouseUpdate(deltaTime);

    m_shader.Bind();

    m_cameraPos.y = m_yPos;
    m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

    m_projection = glm::perspective(glm::radians(m_fov), 800.0f / 600.0f, 0.1f, 100.0f);
    m_shader.SetUniformMatrix4fv("u_MVP", m_projection * m_view * m_model);
    m_shader.SetUniform4f("u_color", m_color[0], m_color[1], m_color[2], m_color[3]);
  }

  void TestQuad3d::onRender(const Renderer &renderer)
  {
    renderer.Draw(*m_vertexArray, *m_indexBuffer, m_shader);
  }

  void TestQuad3d::onImGuiRender()
  {
    ImGui::SliderFloat("Fov", &m_fov, 90.0f, 180.0f);
    ImGui::ColorEdit4("Quad Color", &m_color[0]);

    if (ImGui::Button("Use Camera (esc to stop)")) {
      glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
  }

  void TestQuad3d::onInputUpdate(int deltaTime)
  {
    float cameraSpeed = m_velocity * (deltaTime / 1000.0);

    if (isKeyPressed(m_window, GLFW_KEY_W)) {
      m_cameraPos += cameraSpeed * m_cameraFront;
    }

    if (isKeyPressed(m_window, GLFW_KEY_S)) {
      m_cameraPos -= cameraSpeed * m_cameraFront;
    }

    if (isKeyPressed(m_window, GLFW_KEY_A)) {
      m_cameraPos -= cameraSpeed * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
    }

    if (isKeyPressed(m_window, GLFW_KEY_D)) {
      m_cameraPos += cameraSpeed * glm::normalize(glm::cross(m_cameraFront, m_cameraUp));
    }

    if (isKeyPressed(m_window, GLFW_KEY_SPACE)) {
      m_yPos += cameraSpeed;
    }

    if (isKeyPressed(m_window, GLFW_KEY_LEFT_SHIFT)) {
      m_yPos -= cameraSpeed;
    }

    if (isKeyPressed(m_window, GLFW_KEY_ESCAPE)) {
      glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }

  void TestQuad3d::onMouseUpdate(int deltaTime)
  {
    if (glfwGetInputMode(m_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
      double xpos, ypos;
      glfwGetCursorPos(m_window, &xpos, &ypos);

      float xOffset = xpos - m_lastMouseX;
      float yOffset = m_lastMouseY - ypos;
      m_lastMouseX = xpos;
      m_lastMouseY = ypos;
      
      xOffset *= m_mouseSensitivity;
      yOffset *= m_mouseSensitivity;

      m_yaw   += xOffset;
      m_pitch += yOffset; 

      if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
      }

      if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
      }

      glm::vec3 direction;
      direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      direction.y = sin(glm::radians(m_pitch));
      direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
      m_cameraFront = glm::normalize(direction);
    }
  }
}
#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/glm.hpp"

namespace test {
  class TestQuad3d : public Test
  {
  public:
    TestQuad3d(GLFWwindow *window);
    ~TestQuad3d();

    void onUpdate(int deltaTime) override;
    void onRender(const Renderer &renderer) override;
    void onImGuiRender() override;
  
  private:
    void onInputUpdate(int deltaTime);
    void onMouseUpdate(int deltaTime);

  private:
    GLFWwindow *m_window;
    VertexArray *m_vertexArray;
    VertexBuffer *m_vertexBuffer;
    IndexBuffer *m_indexBuffer;

    Shader m_shader;
    glm::vec4 m_color;
    glm::mat4 m_projection, m_view, m_model;

    float m_fov, m_velocity, m_mouseSensitivity;

    glm::vec3 m_cameraPos, m_cameraFront, m_cameraUp;

    float m_lastMouseX, m_lastMouseY, m_yaw, m_pitch;
  };
}
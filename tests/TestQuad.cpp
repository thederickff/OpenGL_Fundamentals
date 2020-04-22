#include "TestQuad.h"
#include "VertexBufferLayout.h"

#include "glm/gtx/transform.hpp"


// glm::mat4 createProjectionMatrix(float fov, int width, int height, float zNear, float zFar)
// {
// 		float aspectRatio = (float) width / (float) height;
// 		float y_scale = (float) ((1.0f / std::tan(glm::radians(fov / 2.0f))) * aspectRatio);
// 		float x_scale = y_scale / aspectRatio;
// 		float frustum_length = zFar - zNear;

//     glm::mat4 proj;
// 		proj[0][0] = x_scale;
// 		proj[1][1] = y_scale;
// 		proj[2][2] = -((zFar + zNear) / frustum_length);
// 		proj[2][3] = -1;
// 		proj[3][2] = -((2 * zNear * zFar) / frustum_length);
// 		proj[3][3] = 0;

//     return proj;
// }

namespace test {
  
  TestQuad::TestQuad()
  : m_shader("res/shaders/testQuad.shader"), m_color{1, 1, 1, 1}, m_fov(90.0f)
  {
    float vertices[] = {
      -0.5f, -0.5f,  -1.0f,
       0.5f, -0.5f,  -1.0f,
       0.5f,  0.5f,  -1.0f,
      -0.5f,  0.5f,  -1.0f,
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    m_indexBuffer = new IndexBuffer(indices, sizeof(indices));

    VertexBufferLayout layout;
    layout.Push<float>(3);

    m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
  }

  TestQuad::~TestQuad()
  {
    delete m_vertexArray;
    delete m_vertexBuffer;
    delete m_indexBuffer;
  }

  void TestQuad::onUpdate(int deltaTime)
  {
    m_shader.Bind();

    m_projection = glm::perspective(glm::radians(m_fov), 800.0f / 600.0f, 0.1f, 100.0f);
    m_shader.SetUniformMatrix4fv("u_MVP", m_projection * m_view * m_model);
    m_shader.SetUniform4f("u_color", m_color[0], m_color[1], m_color[2], m_color[3]);
  }

  void TestQuad::onRender(const Renderer &renderer)
  {
    renderer.Draw(*m_vertexArray, *m_indexBuffer, m_shader);
  }

  void TestQuad::onImGuiRender()
  {
    ImGui::SliderFloat("Fov", &m_fov, 90.0f, 180.0f);
    ImGui::ColorEdit4("Quad Color", &m_color[0]);
  }

}
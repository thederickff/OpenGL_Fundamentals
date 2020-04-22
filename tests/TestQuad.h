#ifndef __OpenGLFundamentals_TestQuad__
#define __OpenGLFundamentals_TestQuad__

#include "Test.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/glm.hpp"

namespace test {

  class TestQuad : public Test
  {
  public:
    TestQuad();
    ~TestQuad();

    void onUpdate(int deltaTime) override;
    void onRender(const Renderer &renderer) override;
    void onImGuiRender() override;
  
  private:
    VertexArray *m_vertexArray;
    VertexBuffer *m_vertexBuffer;
    IndexBuffer *m_indexBuffer;
    
    Shader m_shader;
    glm::vec4 m_color;
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_model;

    float m_fov;
  };

}

#endif /* defined(__OpenGLFundamentals_TestQuad__) */
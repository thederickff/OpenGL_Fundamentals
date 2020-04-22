#include "TestClearColor.h"

#include "Renderer.h"

namespace test {

  TestClearColor::TestClearColor()
  : m_clearColor { 0.2, 0.3, 0.8, 1.0 }
  {
  }

  TestClearColor::~TestClearColor()
  {
  }


  void TestClearColor::onUpdate(int deltaTime)
  {
  }

  void TestClearColor::onRender(const Renderer &renderer)
  {
    GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
  }

  void TestClearColor::onImGuiRender()
  {
    ImGui::ColorEdit4("Clear Color", m_clearColor);
  }


}

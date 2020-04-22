#ifndef __OpenGLFundamentals_Test__
#define __OpenGLFundamentals_Test__

#include <vector>
#include <functional>

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
  class Test
  {
  public:
    Test() {}
    virtual ~Test() {}

    virtual void onUpdate(int deltaTime) {}
    virtual void onRender(const Renderer& renderer) {}
    virtual void onImGuiRender() {}
  };

  class TestMenu : public Test
  {
  public:
    TestMenu(Test *&currentTest);
    ~TestMenu();

    void onImGuiRender() override;

    void push(const std::string &label, const std::function<Test *()> &testCallback)
    {
      m_tests.push_back(std::make_pair(label, testCallback));
    }

  private:
    Test *&m_currentTest;
    std::vector<std::pair<std::string, std::function<Test *()>>> m_tests;
  };
}

#endif /* defined(__OpenGLFundamentals_Test__) */
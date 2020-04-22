#ifndef __OpenGLFundamentals_Test__
#define __OpenGLFundamentals_Test__

#include <vector>
#include <functional>

namespace test {
  class Test
  {
  public:
    Test() {}
    virtual ~Test() {}

    virtual void onUpdate(int deltaTime) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}
  };

  class TestMenu : public Test
  {
  public:
    TestMenu(Test *&currentTest);
    ~TestMenu();

    void onImGuiRender() override;

    template<typename T>
    void push(const std::string &label)
    {
      m_tests.push_back(std::make_pair(label, [](){ return new T(); }));
    }

  private:
    Test *&m_currentTest;
    std::vector<std::pair<std::string, std::function<Test *()>>> m_tests;
  };
}

#endif /* defined(__OpenGLFundamentals_Test__) */
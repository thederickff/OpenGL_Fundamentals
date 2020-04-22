#ifndef __OpenGLFundadamentals_TestClearColor__
#define __OpenGLFundadamentals_TestClearColor__

#include "Test.h"

namespace test {

  class TestClearColor : public Test
  {
  public:
    TestClearColor();
    ~TestClearColor();

    void onUpdate(int deltaTime) override;
    void onRender() override;
    void onImGuiRender() override;
  private:
    float m_clearColor[4];
  };

}

#endif /* defined(__OpenGLFundadamentals_TestClearColor__) */
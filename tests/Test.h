#ifndef __OpenGLFundamentals_Test__
#define __OpenGLFundamentals_Test__

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

}

#endif /* defined(__OpenGLFundamentals_Test__) */
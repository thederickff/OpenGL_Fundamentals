#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>

struct VertexBufferLayoutElement
{
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    

private:
    std::vector<VertexBufferLayoutElement> m_Elements;
};

#endif // defined(VERTEX_BUFFER_LAYOUT)
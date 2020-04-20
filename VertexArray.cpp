#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1,&m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); ++i) 
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i)); 
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset))); 
        offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererId));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
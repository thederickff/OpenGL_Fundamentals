/* 
 * File:   VertexArray.h
 * Author: derickfelix
 *
 * Created on April 22, 2018, 3:33 PM
 */

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    
    void Bind() const;
    void Unbind() const;
};

#endif /* VERTEXARRAY_H */


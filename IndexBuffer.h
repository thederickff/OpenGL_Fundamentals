#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }

private:
    unsigned int m_RendererId;
    unsigned int m_Count;
};

#endif // defined(INDEX_BUFFER_H)
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexShader;
    std::string FragmentShader;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    // caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
};

#endif // defined(SHADER_H)
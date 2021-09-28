#include "Shader.h"

Shader::Shader(const std::string& filePath)
	:	m_FilePath(filePath),
		m_RendererID(0)
{
    auto shaderProgramSources = ParseShader(filePath);
    m_RendererID = std::apply(CreateShader, shaderProgramSources);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, const Uniform4f& uniform)
{
    GLCall(glUniform4f(GetUniformLocation(name), uniform.v0,uniform.v1,uniform.v2,uniform.v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& uniformName) const
{
    if (m_Uniforms.find(uniformName) != m_Uniforms.end())
        return m_Uniforms[uniformName];

    GLCall(int location = glGetUniformLocation(m_RendererID, uniformName.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << uniformName << "' doesn't exist.\n";
    m_Uniforms[uniformName] = location;
    return location;
}

Shader::ShaderID Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(ShaderID program = glCreateProgram());
    CompShaderID vertShader = CompileShader(vertexShader, GL_VERTEX_SHADER);
    CompShaderID fragShader = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vertShader));
    GLCall(glAttachShader(program, fragShader));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
          
    GLCall(glDeleteShader(vertShader));
    GLCall(glDeleteShader(fragShader));

    return program;
}


Shader::CompShaderID Shader::CompileShader(const std::string& source, unsigned int type)
{
    ShaderID ID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(ID, 1, &src, nullptr);
    glCompileShader(ID);

    int compilationResult;
    auto checkCompilationStatus = [&]()
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &compilationResult);

        if (compilationResult == GL_FALSE)
        {
            int lenght;
            glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &lenght);
            char* msg = (char*)_malloca(lenght * sizeof(char));
            glGetShaderInfoLog(ID, lenght, &lenght, msg);
            std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                << " shader!\n" << msg << std::endl;
            glDeleteShader(ID);
        }
    };
    checkCompilationStatus();
    return (compilationResult == GL_FALSE) ? -1 : ID;
}

std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filePath)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream file(filePath);
    if (!file.good())
    {
        std::cerr << "Failed to open shader file named " << filePath;
        return std::make_tuple("", "");
    }
    std::stringstream parsedShader[2];
    ShaderType type = ShaderType::NONE;


    std::string line;

    while (getline(file, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
            parsedShader[static_cast<int>(type)] << line << '\n';
    }

    return std::make_tuple(parsedShader[0].str(),
        parsedShader[1].str());

}

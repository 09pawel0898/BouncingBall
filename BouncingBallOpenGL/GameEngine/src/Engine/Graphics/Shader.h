#pragma once

#include "../Core/Core.h"

class Shader
{
public:
	using ShaderID = unsigned int;
	using CompShaderID = unsigned int;

	struct Uniform4f
	{
		float v0, v1, v2, v3;
	};
private:
	unsigned m_RendererID;
	std::string m_FilePath;
	mutable std::unordered_map<std::string, int> m_Uniforms;
public:
	Shader(const std::string& filePath);
	~Shader();

	inline void Bind() const;
	inline void Unbind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, const Uniform4f& uniform);
	void SetUniformMat4f(const std::string& name, const glm::mat4& uniform);
private:
	int GetUniformLocation(const std::string& uniformName) const;

private:
	static ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static CompShaderID CompileShader(const std::string& source, unsigned int type);
	static std::tuple<std::string, std::string> ParseShader(const std::string& filePath);
};

inline void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

inline void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}


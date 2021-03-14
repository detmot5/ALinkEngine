#include "alinkpch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <filesystem>

#include "OpenGLShader.h"
namespace ALink {

static GLenum ShaderTypeFromString(const std::string& type) {
  if (type == "vertex")                        return GL_VERTEX_SHADER;
  if (type == "fragment" || type == "pixel")   return GL_FRAGMENT_SHADER;

  ALINK_ENGINE_ASSERT(false, "OpenglShader - ShaderTypeFromString "
                                            "- Unknown Shader Type");
  return 0;
}


OpenGLShader::OpenGLShader(const std::string& name,
                           const std::string& vertexSrc,
                           const std::string& fragmentSrc)
  : name(name) {
  std::unordered_map<GLenum, std::string> sources;
  sources[GL_VERTEX_SHADER] = vertexSrc;
  sources[GL_FRAGMENT_SHADER] = fragmentSrc;
  this->Compile(sources);
}

OpenGLShader::OpenGLShader(const std::string& filePath) {
  std::string source = this->ReadFile(filePath);
  auto preProcessedShaderSources = this->PreProcess(source);
  this->Compile(preProcessedShaderSources);
  this->name = std::filesystem::path(filePath).stem().string();
}

OpenGLShader::~OpenGLShader() { glDeleteProgram(this->rendererID); }

void OpenGLShader::Bind() { glUseProgram(this->rendererID); }

void OpenGLShader::Unbind() { glUseProgram(0); }


void OpenGLShader::SetUniformInt(const std::string& name, int value) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniform1i(location, value);
}
void OpenGLShader::SetUniformFloat(const std::string& name, float value) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniform1f(location, value);
}
void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& value) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniform2f(location, value.x, value.y);
}
void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniform3f(location, value.x, value.y, value.z);
}
void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniform4f(location, value.x, value.y, value.z, value.w);
}
void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
  GLint location = glGetUniformLocation(this->rendererID, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
    // Create an empty vertex shader handle
  GLuint program = glCreateProgram();
  std::vector<GLenum> shaderIds;
  shaderIds.reserve(shaderSources.size());
  for (auto[type, source] : shaderSources) {

    GLuint shader = glCreateShader(type);
    const GLchar *sourcePtr = (const GLchar *)source.c_str();
    glShaderSource(shader, 1, &sourcePtr, 0);
    // Compile the vertex shader
    glCompileShader(shader);
  
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
      glDeleteShader(shader);
      ALINK_ENGINE_ASSERT(false, "Shader compilation error {0}", infoLog.data());

      break;
    }
    glAttachShader(program, shader);
    shaderIds.push_back(shader);
  }
  this->rendererID = program;

  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, reinterpret_cast<int*>(&isLinked));
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
    
    glDeleteProgram(program);
  
    for (auto shaderID : shaderIds) {
      glDeleteShader(shaderID);
    }

    ALINK_ENGINE_ASSERT(false, "Shader Link error {0}", infoLog.data());
    return;
  }

  // Always detach shaders after a successful link.
  for (auto shaderID : shaderIds) {
    glDetachShader(program, shaderID);
  }


}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
  std::unordered_map<GLenum, std::string> shaderSources;
  static const char* typeToken = "#type";
  size_t typeTokenLength = std::strlen(typeToken);
  size_t pos = source.find(typeToken, 0);
  while (pos != std::string::npos) {
    size_t eol = source.find_first_of("\r\n", pos);
    ALINK_ENGINE_ASSERT(eol != std::string::npos, "Failed to compile shader"
                                                  " - syntax error in shader type");
    size_t begin = pos + typeTokenLength + 1;
    std::string type = source.substr(begin, eol - begin);
    ALINK_ENGINE_ASSERT(ShaderTypeFromString(type) != 0,
                        "Failed to compile shader"
                        "Invalid shader type specification");

    size_t nextLinePos = source.find_first_not_of("\r\n", eol);
    pos = source.find(typeToken, nextLinePos);
    shaderSources[ShaderTypeFromString(type)] =
      source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
  }
  return shaderSources;
}

std::string OpenGLShader::ReadFile(const std::string& filePath) {
  std::ifstream input(filePath, std::ios::in | std::ios::binary);
  ALINK_ENGINE_ASSERT(input, "Failed to read file");

  std::string result;
  input.seekg(0, std::ios::end);
  result.resize(input.tellg());
  input.seekg(0, std::ios::beg);
  input.read(result.data(), result.size());
  input.close();
  return result;
}

}

#include "alinkpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace ALink {

OpenGLShader::OpenGLShader(const std::string& vertexSrc,
               const std::string& fragmentSrc) {

  // Create an empty vertex shader handle
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Send the vertex shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  const GLchar *source = (const GLchar *)vertexSrc.c_str();
  glShaderSource(vertexShader, 1, &source, 0);

  // Compile the vertex shader
  glCompileShader(vertexShader);

  GLint isCompiled = 0;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
    ALINK_ENGINE_LOG_ERROR("SHader Compilation error");
    ALINK_ENGINE_LOG_ERROR("{0}", infoLog.data());
    
    // We don't need the shader anymore.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.
    
    // In this simple program, we'll just leave
    return;
  }

  // Create an empty fragment shader handle
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Send the fragment shader source code to GL
  // Note that std::string's .c_str is NULL character terminated.
  source = (const GLchar *)fragmentSrc.c_str();
  glShaderSource(fragmentShader, 1, &source, 0);

  // Compile the fragment shader
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
    ALINK_ENGINE_LOG_ERROR("SHader Link error");
    ALINK_ENGINE_LOG_ERROR("{0}", infoLog.data());
    // We don't need the shader anymore.
    glDeleteShader(fragmentShader);
    // Either of them. Don't leak shaders.
    glDeleteShader(vertexShader);

    // Use the infoLog as you see fit.
    
    // In this simple program, we'll just leave
    return;
  }

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  GLuint program = glCreateProgram();
  this->rendererID = program;

  // Attach our shaders to our program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
    ALINK_ENGINE_LOG_ERROR("SHader Compilation error");
    ALINK_ENGINE_LOG_ERROR("{0}", infoLog.data());
    // We don't need the program anymore.
    glDeleteProgram(program);
    // Don't leak shaders either.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use the infoLog as you see fit.
    
    // In this simple program, we'll just leave
    return;
  }

  // Always detach shaders after a successful link.
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

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

}
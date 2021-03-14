#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLSHADER_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLSHADER_H_
#include "Renderer/Shader.h"

#include <glm/glm.hpp>
namespace ALink {

class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
  explicit OpenGLShader(const std::string& filePath);
  ~OpenGLShader();
  void Bind() override;
  void Unbind() override;


  void SetUniformInt(const std::string& name, int value);
  void SetUniformFloat(const std::string& name, float value);
  void SetUniformFloat2(const std::string& name, const glm::vec2& value);
  void SetUniformFloat3(const std::string& name, const glm::vec3& value);
  void SetUniformFloat4(const std::string& name, const glm::vec4& value);
  void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
  void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

  inline const std::string& GetName() const override { return this->name; };
 private:
  void Compile(const std::unordered_map<unsigned int, std::string>& shaderSources);
  std::unordered_map<unsigned int, std::string> PreProcess(const std::string& source);
  std::string ReadFile(const std::string& filepath);
 private:
  uint32_t rendererID;
  std::string name;
};

}  // namespace ALink



#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLSHADER_H_

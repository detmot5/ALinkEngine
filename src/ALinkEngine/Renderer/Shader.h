#ifndef ALINKENGINE_RENDERER_SHADER_H_
#define ALINKENGINE_RENDERER_SHADER_H_
#include <glm/glm.hpp>
namespace ALinkEngine {

class Shader {
 public:
  Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~Shader();
  void Bind();
  void Unbind();
  void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
 private:
  uint32_t rendererID;
};

} // namespace ALinkEngine


#endif  // ALINKENGINE_RENDERER_SHADER_H_


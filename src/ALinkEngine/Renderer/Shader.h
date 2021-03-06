#ifndef ALINKENGINE_RENDERER_SHADER_H_
#define ALINKENGINE_RENDERER_SHADER_H_
#include "alinkpch.h"

namespace ALinkEngine {

class Shader {
 public:
  Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
  ~Shader();
  void Bind();
  void Unbind();
 private:
  uint32_t rendererID;
};

} // namespace ALinkEngine


#endif  // ALINKENGINE_RENDERER_SHADER_H_


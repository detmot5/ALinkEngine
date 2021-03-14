#ifndef ALINKENGINE_RENDERER_SHADERLIBRARY_H_
#define ALINKENGINE_RENDERER_SHADERLIBRARY_H_
#include "Shader.h"


namespace ALink {
  
class ShaderLibrary {
 public:
  void Add(const std::shared_ptr<Shader>& shader);
  std::shared_ptr<Shader> Load(const std::string& filePath);
  std::shared_ptr<Shader> GetShader(const std::string& name);
 private:
  bool IsShaderExists(const std::string& name);

 private:
  std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

}  // namespace ALink




#endif  // ALINKENGINE_RENDERER_SHADERLIBRARY_H_

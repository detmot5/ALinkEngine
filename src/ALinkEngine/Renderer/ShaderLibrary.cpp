#include "alinkpch.h"
#include "ShaderLibrary.h"


namespace ALink {
void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader) {
  auto& name = shader->GetName();
  ALINK_ENGINE_ASSERT(!this->IsShaderExists(name), "Shader already exist!");
  this->shaders[name] = shader;
}


std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filePath) {
  auto shader = Shader::Create(filePath);
  this->Add(shader);
  return shader;
}

std::shared_ptr<Shader> ShaderLibrary::GetShader(const std::string& name) {
  ALINK_ENGINE_ASSERT(this->IsShaderExists(name), "Shader not found!");
  return this->shaders[name];
}

bool ShaderLibrary::IsShaderExists(const std::string& name) {
  return this->shaders.find(name) != shaders.end();
}
}   // namespace ALink
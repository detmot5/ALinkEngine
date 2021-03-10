#ifndef ALINKENGINE_RENDERER_SHADER_H_
#define ALINKENGINE_RENDERER_SHADER_H_
namespace ALink {

class Shader {
 public:
  virtual ~Shader() = default;
  virtual void Bind() = 0;
  virtual void Unbind() = 0;
  static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};

}  // namespace ALink


#endif  // ALINKENGINE_RENDERER_SHADER_H_


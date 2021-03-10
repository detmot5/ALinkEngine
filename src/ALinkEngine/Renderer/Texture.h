#ifndef ALINKENGINE_RENDERER_TEXTURE_H_
#define ALINKENGINE_RENDERER_TEXTURE_H_

namespace ALink {
class Texture {
 public:
  virtual ~Texture() = default;
  virtual uint32_t GetWidth() const = 0;
  virtual uint32_t GetHeight() const = 0;
  virtual void Bind(uint32_t slot = 0) const = 0;
};

class Texture2D : public Texture {
 public:
  static std::shared_ptr<Texture2D> Create(const std::string& path);
};

}  // namespace ALink



#endif  // ALINKENGINE_RENDERER_TEXTURE_H_

#ifndef ALINKENGINE_RENDERER_BUFFER_H_
#define ALINKENGINE_RENDERER_BUFFER_H_

namespace ALink {

enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool,
};

static uint32_t GetShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:   return 4;
    case ShaderDataType::Float2:  return 4 * 2;
    case ShaderDataType::Float3:  return 4 * 3;
    case ShaderDataType::Float4:  return 4 * 4;
    case ShaderDataType::Mat3:    return 4 * 3 * 3;
    case ShaderDataType::Mat4:    return 4 * 4 * 4;
    case ShaderDataType::Int:     return 4;
    case ShaderDataType::Int2:    return 4 * 2;
    case ShaderDataType::Int3:    return 4 * 3;
    case ShaderDataType::Int4:    return 4 * 4;
    case ShaderDataType::Bool:    return 1;
  }
  ALINK_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint32_t offset;
  uint32_t size;
  bool isNormalized;

  BufferElement() {}
  BufferElement(ShaderDataType type, const std::string& name, bool isNormalized = false)
    : name(name),
      type(type),
      offset(0),
      size(GetShaderDataTypeSize(type)),
      isNormalized(isNormalized) {}
      
  static uint32_t GetElementsCount(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Float:   return 1;
      case ShaderDataType::Float2:  return 2;
      case ShaderDataType::Float3:  return 3;
      case ShaderDataType::Float4:  return 4;
      case ShaderDataType::Mat3:    return 3 * 3;
      case ShaderDataType::Mat4:    return 4 * 4;
      case ShaderDataType::Int:     return 1;
      case ShaderDataType::Int2:    return 2;
      case ShaderDataType::Int3:    return 3;
      case ShaderDataType::Int4:    return 4;
      case ShaderDataType::Bool:    return 1;
    }
    ALINK_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
};

class BufferLayout {

 public:
  BufferLayout() {}
  BufferLayout(const std::initializer_list<BufferElement>& elements)
    : elements(elements) {
    CalculateOffsetAndStride();
  }
  inline uint32_t GetStride() const { return this->stride; }
  inline const std::vector<BufferElement>& GetElements() const { return this->elements; }
  inline std::vector<BufferElement>::iterator begin() { return this->elements.begin(); }
  inline std::vector<BufferElement>::iterator end() { return this->elements.end(); }
  inline std::vector<BufferElement>::const_iterator begin() const { return this->elements.begin(); }
  inline std::vector<BufferElement>::const_iterator end() const { return this->elements.end(); }

 private:
  void CalculateOffsetAndStride() {
    uint32_t offset = 0;
    this->stride = 0;
    for (auto& element : elements) {
      element.offset = offset;
      offset += element.size;
      this->stride += element.size;
    }
  }
  
 private:
  std::vector<BufferElement> elements;
  uint32_t stride;
};

class VertexBuffer {
 public:
  virtual ~VertexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void SetLayout(const BufferLayout& layout) = 0;
  virtual const BufferLayout& GetLayout() const = 0;

  static std::shared_ptr<VertexBuffer> Create(float* verticies, uint32_t size);
};

class IndexBuffer {
 public:
  virtual ~IndexBuffer() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual uint32_t GetCount() const = 0;

  static std::shared_ptr<IndexBuffer> Create(uint32_t* indicies, uint32_t count);
};

}  // namespace ALink

#endif  // ALink_RENDERER_BUFFER_H_

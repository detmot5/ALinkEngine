#include "alinkpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace ALink {
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    : path(path) {
    int width, height, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ALINK_ENGINE_ASSERT(data != nullptr, "Failed to load texture - data is nullptr");

    GLenum internalFormat = 0;
    GLenum dataFormat = 0;

    if (channels == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    } else if (channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }
    ALINK_ENGINE_ASSERT(internalFormat != 0 && dataFormat != 0, "Texture format not supported!");
    this->width = width;
    this->height = height;
    glGenTextures(1, &this->rendererID);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
    glTextureStorage2D(this->rendererID, 1, internalFormat, this->width, this->height);
    glTextureParameteri(this->rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(this->rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureSubImage2D(this->rendererID, 0, 0, 0, this->width, this->height, dataFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }
  OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &this->rendererID);
  }
  void OpenGLTexture2D::Bind(uint32_t slot) const {
    glBindTextureUnit(slot, this->rendererID);
  }
}  // namespace ALink

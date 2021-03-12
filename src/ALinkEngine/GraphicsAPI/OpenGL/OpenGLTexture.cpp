#include "alinkpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace ALink {
  OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    : path(path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ALINK_ENGINE_ASSERT(data != nullptr, "{0} Failed to load texture - data is nullptr", path);

    GLenum internalFormat = 0;
    GLenum dataFormat = 0;

    if (channels == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    } else if (channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }
    ALINK_ENGINE_ASSERT(internalFormat != 0 && dataFormat != 0, "{0} Texture format not supported!", path);
    this->width = width;
    this->height = height;
    glGenTextures(1, &this->rendererID);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->width, this->height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
  }
  OpenGLTexture2D::~OpenGLTexture2D() {
    glDeleteTextures(1, &this->rendererID);
  }
  void OpenGLTexture2D::Bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
  }
}  // namespace ALink

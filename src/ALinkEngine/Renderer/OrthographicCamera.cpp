#include "alinkpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace ALinkEngine {
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
  : projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(1.0f) {
  this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}





void OrthographicCamera::SetPosition(const glm::vec3& position) {
  this->position = position;
  this->RecalculateViewMatrix();
}

void OrthographicCamera::SetRotation(float rotation)  {
  this->rotation = rotation;
  this->RecalculateViewMatrix();
}

void OrthographicCamera::RecalculateViewMatrix() {
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0, 0, 1));

  this->viewMatrix = glm::inverse(transform);
  this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
}
}
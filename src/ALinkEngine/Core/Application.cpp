#include "Application.h"

namespace ALinkEngine {

ALinkApplication::ALinkApplication() {
  ALINK_ENGINE_ASSERT(ALinkApplication::instance == nullptr,
                      "There can be only one application!");
  ALinkApplication::instance = this;
}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
  Logger::Init();
  this->window = std::make_unique<Window>(WindowProps());
  this->isRunning = true;
  this->window->SetEventCallback(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnEvent));
  this->imGuiLayer = new ImGuiLayer();
  this->AddOverlay(this->imGuiLayer);

  float verticies[3 * 7] = {
    -0.5f, -0.5f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.0f,  0.5f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f
  };

  uint32_t indicies[] = {
      0,
      1,
      2,
  };

  glGenVertexArrays(1, &this->vertexArray);
  glBindVertexArray(this->vertexArray);
  this->vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
  this->indexBuffer.reset(IndexBuffer::Create(indicies, 3));
  
  vertexBuffer->SetLayout({
    {ShaderDataType::Float3, "a_Position"},
    {ShaderDataType::Float4, "a_Color"},
  });
  

  const auto& layout = vertexBuffer->GetLayout();
  uint32_t index = 0;
  for (const auto& element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
      index,
      BufferElement::GetComponentElementsCount(element.type),
      GL_FLOAT,
      element.isNormalized ? GL_TRUE : GL_FALSE,
      layout.GetStride(),
      (const void*) element.offset);
    index++;
  }

  glEnableVertexAttribArray(0);


  std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 a_Position;
    layout(location = 1) in vec4 a_Color;
    out vec3 v_Position;
    out vec4 v_Color;

    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = vec4(a_Position, 1.0);
      
    }
  )";

  std::string fragmentSrc = R"(
    #version 330 core
    layout(location = 0) out vec4 color;
    in vec3 v_Position;
    in vec4 v_Color;
    void main() {
      color = vec4(v_Position * 0.5 + 0.5, 1.0);
      color = v_Color;
    }
  )";

  this->shader.reset(new Shader(vertexSrc, fragmentSrc));
}

void ALinkApplication::InternalEvents() {
  // temporaty as fuck !
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  this->shader->Bind();
  glBindVertexArray(this->vertexArray);
  glDrawElements(GL_TRIANGLES, this->indexBuffer->GetCount(), GL_UNSIGNED_INT,
                 nullptr);

  for (auto layer : this->layerStack) {
    layer->OnUpdate();
  }

  this->imGuiLayer->Begin();
  for (auto layer : this->layerStack) {
    layer->OnImGuiRender();
  }
  this->imGuiLayer->End();

  this->window->OnUpdate();
}

void ALinkApplication::AddLayer(Layer* layer) {
  this->layerStack.AddLayer(layer);
  layer->OnAttach();
}

void ALinkApplication::AddOverlay(Layer* overlay) {
  this->layerStack.AddOverlay(overlay);
  overlay->OnAttach();
}

void ALinkApplication::OnEvent(Event& event) {
  EventDispatcher dispacher(event);
  dispacher.Dispatch<WindowCloseEvent>(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnWindowCloseEvent));

  for (auto it = this->layerStack.rbegin(); it != this->layerStack.rend();
       it++) {
    if (!event.isHandled) (*it)->OnEvent(event);
  }
}

bool ALinkApplication::OnWindowCloseEvent(WindowCloseEvent& event) {
  this->isRunning = false;
  return true;
}

}  // namespace ALinkEngine

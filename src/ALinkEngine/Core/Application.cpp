#include "alinkpch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include <glad/glad.h>

namespace ALinkEngine {

ALinkApplication::ALinkApplication() :
  camera(-1.6f, 1.6f, -0.9f, 0.9f) {
  Logger::Init();
  ALINK_ENGINE_ASSERT(ALinkApplication::instance == nullptr,
                      "There can be only one application!");
  ALinkApplication::instance = this;
}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
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

  this->vertexArray = VertexArray::Create();
  std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(verticies, sizeof(verticies));
  std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indicies, 3);
  vertexBuffer->SetLayout({
    {ShaderDataType::Float3, "a_Position"},
    {ShaderDataType::Float4, "a_Color"},
  });

  this->vertexArray->AddVertexBuffer(vertexBuffer);
  this->vertexArray->SetIndexBuffer(indexBuffer);


  this->squareVA = VertexArray::Create();

  float sqverticies[4 * 7] = {
    -0.75f, -0.75f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.75f, -0.75f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
     0.75f,  0.75f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.75f,  0.75f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f
  };

  std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(sqverticies, sizeof(sqverticies));
  squareVB->SetLayout({
    {ShaderDataType::Float3, "a_Position"},
    {ShaderDataType::Float4, "a_Color"},
  });
  squareVA->AddVertexBuffer(squareVB);
  uint32_t sqindicies[] = {
      0, 1, 2,
      2, 3, 0
  };

  std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(sqindicies, 6);
  squareVA->SetIndexBuffer(squareIB);



  std::string vertexSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 a_Position;
    layout(location = 1) in vec4 a_Color;
    out vec3 v_Position;
    out vec4 v_Color;

    uniform mat4 u_ViewProjection;
    void main() {
      v_Position = a_Position;
      v_Color = a_Color;
      gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
      
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
  glViewport(0, 0, this->window->GetWidth(), this->window->GetHeight());
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
  dispacher.Dispatch<KeyPressedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnKeyPressedEvent));

  for (auto it = this->layerStack.rbegin(); it != this->layerStack.rend();
       it++) {
    if (!event.isHandled) (*it)->OnEvent(event);
  }
}

bool ALinkApplication::OnWindowCloseEvent(WindowCloseEvent& event) {
  this->isRunning = false;
  return true;
}

bool ALinkApplication::OnKeyPressedEvent(KeyPressedEvent& event) {
  auto keyCode = event.GetKeyCode();
  if (keyCode == Key::W) {
    auto pos = camera.GetPosition();
    pos.y += 0.02f;
    camera.SetPosition(pos);
  } else if (keyCode == Key::S) {
    auto pos = camera.GetPosition();
    pos.y -= 0.02f;
    camera.SetPosition(pos);
  } else if (keyCode == Key::A) {
    auto pos = camera.GetPosition();
    pos.x -= 0.02f;
    camera.SetPosition(pos);
  } else if (keyCode == Key::D) {
    auto pos = camera.GetPosition();
    pos.x += 0.02f;
    camera.SetPosition(pos);
  }


  return false;
}

}  // namespace ALinkEngine

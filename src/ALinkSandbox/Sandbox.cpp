#include <ALinkEngine.h>

#include <iostream>

class ExampleLayer : public ALink::Layer {
 public:
  explicit ExampleLayer(const std::string& name) : Layer(name), camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

  void OnAttach() override {
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

    this->vertexArray = ALink::VertexArray::Create();
    std::shared_ptr<ALink::VertexBuffer> vertexBuffer = ALink::VertexBuffer::Create(verticies, sizeof(verticies));
    std::shared_ptr<ALink::IndexBuffer> indexBuffer = ALink::IndexBuffer::Create(indicies, 3);
    vertexBuffer->SetLayout({
      {ALink::ShaderDataType::Float3, "a_Position"},
      {ALink::ShaderDataType::Float4, "a_Color"},
    });

    this->vertexArray->AddVertexBuffer(vertexBuffer);
    this->vertexArray->SetIndexBuffer(indexBuffer);


    this->squareVA = ALink::VertexArray::Create();

    float sqverticies[4 * 7] = {
      -0.75f, -0.75f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
      0.75f, -0.75f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
      0.75f,  0.75f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,
      -0.75f,  0.75f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f
    };

    std::shared_ptr<ALink::VertexBuffer> squareVB = ALink::VertexBuffer::Create(sqverticies, sizeof(sqverticies));
    squareVB->SetLayout({
      {ALink::ShaderDataType::Float3, "a_Position"},
      {ALink::ShaderDataType::Float4, "a_Color"},
    });
    squareVA->AddVertexBuffer(squareVB);
    uint32_t sqindicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<ALink::IndexBuffer> squareIB = ALink::IndexBuffer::Create(sqindicies, 6);
    squareVA->SetIndexBuffer(squareIB);

    camera.SetRotation(90.0f);

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

    this->shader.reset(new ALink::Shader(vertexSrc, fragmentSrc));
    
  }

  void OnUpdate(ALink::TimeStep ts) override {
    using namespace ALink;
    ALINK_LOG_INFO("Current Timestep: {0}", ts.GetSeconds());
    float spd = 5 * ts;
    if (ALink::Input::IsKeyPressed(Key::W)) {
      auto pos = camera.GetPosition();
      pos.y += spd;
      camera.SetPosition(pos);
    } else if (ALink::Input::IsKeyPressed(Key::S)) {
      auto pos = camera.GetPosition();
      pos.y -= spd;
      camera.SetPosition(pos);
    } else if (ALink::Input::IsKeyPressed(Key::A)) {
      auto pos = camera.GetPosition();
      pos.x -= spd;
      camera.SetPosition(pos);
    } else if (ALink::Input::IsKeyPressed(Key::D)) {
      auto pos = camera.GetPosition();
      pos.x += spd;
      camera.SetPosition(pos);
    } else if (ALink::Input::IsKeyPressed(Key::Q)) {
      auto rotation = camera.GetRotation();
      camera.SetRotation(rotation += 180.0f * ts);
    } else if (ALink::Input::IsKeyPressed(Key::E)) {
      auto rotation = camera.GetRotation();
      camera.SetRotation(rotation -= 180.0f * ts);
    }



    ALink::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    ALink::RenderCommand::Clear();
    ALink::Renderer::BeginScene(this->camera);
    ALink::Renderer::Submit(this->shader, this->squareVA);
    ALink::Renderer::Submit(this->shader, this->vertexArray);
    ALink::Renderer::EndScene();
  }

  void OnEvent(ALink::Event& event) override {
    ALink::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ALink::KeyPressedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ExampleLayer::OnKeyPressedEvent));
  }

  bool OnKeyPressedEvent(ALink::KeyPressedEvent event) {
    return false;
  }

  void OnImGuiRender() override {
    ImGui::Begin("Doopa");
    if (ImGui::Button("click")) {
      ALINK_LOG_INFO("Ouch");
    }
    ImGui::End();
  }

 private:
  std::shared_ptr<ALink::Shader> shader;
  std::shared_ptr<ALink::VertexArray> vertexArray;

  std::shared_ptr<ALink::VertexArray> squareVA;
  ALink::OrthographicCamera camera;
};

class SandBox : public ALink::ALinkApplication {
 public:
  void Init() override { this->AddLayer(new ExampleLayer("Dupa")); }

  void ShutDown() override {}

  void Run() override {}
};

ALink::ALinkApplication* ALink::CreateApplication() {
  return new SandBox();
}

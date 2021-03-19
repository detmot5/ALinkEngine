#include <ALinkEngine.h>

#include <iostream>
#include <filesystem>

class ExampleLayer : public ALink::Layer {
 public:
  explicit ExampleLayer(const std::string& name)
    : Layer(name),
      cameraController(1600.0f / 900.0f) {}

  void OnAttach() override {
    float verticies[3 * 7] = {
     -1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
      1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f
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

    float sqverticies[4 * 5] = {
      -0.9f, -0.75f, 1.0f,  0.0f, 0.0f,
       0.9f, -0.75f, 1.0f,  1.0f, 0.0f,
       0.9f,  0.75f, 1.0f,  1.0f, 1.0f,
      -0.9f,  0.75f, 1.0f,  0.0f, 1.0f
    };

    std::shared_ptr<ALink::VertexBuffer> squareVB = ALink::VertexBuffer::Create(sqverticies, sizeof(sqverticies));
    squareVB->SetLayout({
      {ALink::ShaderDataType::Float3, "a_Position"},
      {ALink::ShaderDataType::Float2, "a_TextureCoords"},
    });
    squareVA->AddVertexBuffer(squareVB);
    uint32_t sqindicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::shared_ptr<ALink::IndexBuffer> squareIB = ALink::IndexBuffer::Create(sqindicies, 6);
    squareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
      #version 330 compatibility
      layout(location = 0) in vec3 a_Position;
      out vec3 v_Position;
      out vec4 v_Color;
      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;
      void main() {
        v_Position = a_Position;

        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
        
      }
    )";

    std::string fragmentSrc = R"(
      #version 330 compatibility
      layout(location = 0) out vec4 color;
      in vec3 v_Position;
      uniform vec4 u_Color;
      void main() {
        //color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = u_Color;
        
      }
    )";

    ALINK_LOG_INFO("{0}", std::filesystem::current_path().filename().string());
    this->shader = ALink::Shader::Create("dupa", vertexSrc, fragmentSrc);
    this->shaderLib.Load("../../../../assets/shaders/Texture.glsl");
    
// TODO(me): Do something with this shit
#ifdef ALINK_PLATFORM_WINDOWS
    std::string texPath = "../../../../assets/images/cubes.png";
#else
    std::string texPath = "/mnt/share/assets/images/cubes.png";
#endif  // ALINK_PLATFORM_WINDOWS
    this->cubesTexture = ALink::Texture2D::Create(texPath);

    auto openglsh = std::dynamic_pointer_cast<ALink::OpenGLShader>(this->shader);
    openglsh->Bind();
    openglsh->SetUniformInt("u_Texture", 0);
  }

  void OnUpdate(ALink::TimeStep ts) override {
    this->cameraController.OnUpdate(ts);
    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.0f));
  
    ALink::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    ALink::RenderCommand::Clear();
    ALink::Renderer::BeginScene(this->cameraController.GetCamera());
    auto openglsh = std::dynamic_pointer_cast<ALink::OpenGLShader>(this->shader);
    openglsh->SetUniformFloat4("u_Color", this->mainColor);
    for (int i = 0; i < 20; i++) {
      for (int j = 0 ; j < 20; j++) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.2f * i, 0.2f * j, 0.0f));
        openglsh->SetUniformFloat4("u_Color", this->mainColor);
        ALink::Renderer::Submit(this->shader, this->squareVA, transform * scale);
      }
    }

    auto textureShader = this->shaderLib.GetShader("Texture");
    this->cubesTexture->Bind();
    ALink::Renderer::Submit(textureShader, this->squareVA,
                                          glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 0.0f)));
    ALink::Renderer::EndScene();
  }

  void OnEvent(ALink::Event& event) override {
    ALink::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<ALink::KeyPressedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ExampleLayer::OnKeyPressedEvent));
    this->cameraController.OnEvent(event);
  }

  bool OnKeyPressedEvent(ALink::KeyPressedEvent event) {
    return false;
  }

  void OnImGuiRender() override {
    ImGui::Begin("Doopa");
    ImGui::ColorEdit3("Main Color", glm::value_ptr(this->mainColor));
    ImGui::End();
  }

 private:
  ALink::ShaderLibrary shaderLib;
  std::shared_ptr<ALink::Shader> shader;
  std::shared_ptr<ALink::VertexArray> vertexArray;
  std::shared_ptr<ALink::VertexArray> squareVA;
  std::shared_ptr<ALink::Texture2D> cubesTexture;
  std::shared_ptr<ALink::Texture2D> boardTexture;
  glm::vec3 squarePosition = {0.5f, -0.5f, 0.0f};
  glm::vec4 mainColor = {0.0f, 0.0f, 1.0f, 1.0f};
  ALink::OrthographicCameraController cameraController;

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

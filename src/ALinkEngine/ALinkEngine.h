#ifndef ALINKENGINE_ALINKENGINE_H_
#define ALINKENGINE_ALINKENGINE_H_
// 3rd party
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Events
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

// Gui
#include "GUI/ImGuiLayer.h"

// Core
#include "Core/Logger.h"
#include "Core/EntryPoint.h"
#include "Core/Application.h"
#include "Core/Layer.h"
#include "Core/Input.h"
#include "Core/TimeStep.h"
#include "Core/Core.h"

// Renderer
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/OrthographicCameraController.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"
#include "Renderer/ShaderLibrary.h"



// TEMPORTARY
#include "GraphicsAPI/OpenGL/OpenGLShader.h"
#endif  // ALINKENGINE_ALINKENGINE_H_


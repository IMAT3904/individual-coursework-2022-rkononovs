/* \file RendererCommon.h */
#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include "platform/OpenGL/OpenGLTexture.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include "rendering/TextureUnitManager.h"
#include "rendering/shaderDataType.h"
#include "systems/loggerSys.h"

namespace Engine {
	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
	class RendererCommon {
	public:
		static TextureUnitManager s_textureUnitManager; //!< texture unit manager
	};
}
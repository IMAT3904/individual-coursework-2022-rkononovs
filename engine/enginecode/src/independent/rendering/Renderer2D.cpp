/* \file Renderer2D.cpp */
#include "engine_pch.h"
#include "rendering/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;

	void Renderer2D::init() {
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx, 0));
		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.0f);

		s_data->shader.reset(new OpenGLShader("./assets/shaders/quad1.glsl"));

		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5,  -0.5f, 1.f, 0.f
		};

		uint32_t indices[4] = { 0,1,2,3 };

		UniformBufferLayout quadLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };
		s_data->quadUBO.reset(new OpenGLUniformBuffer(quadLayout));

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;

		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices), VertexBufferLayout({ ShaderDataType::Float2, ShaderDataType::Float2 })));
		IBO.reset(new OpenGLIndexBuffer(indices, 4));

		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->quadUBO->attachShaderBlock(s_data->shader, "b_cameraQuad");

		// Path to font file
		const char* filePath = "./assets/fonts/arial.ttf";

		//Set the dim of the glyph buffer
		s_data->glyphBufferDims = { 256, 256 };
		s_data->glyphBufferSize = s_data->glyphBufferDims.x * s_data->glyphBufferDims.y * 4 * sizeof(unsigned char);
		s_data->glyphBuffer.reset(static_cast<unsigned char*>(malloc(s_data->glyphBufferSize)));

		// Init freetype
		if (FT_Init_FreeType(&s_data->ft)) LoggerSys::error("Error: Freetype could not initialise.");

		// Load font
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->font)) LoggerSys::error("Error: Freetype could not load font: {0}", filePath);

		// Set the char size
		int32_t charSize = 86;
		if (FT_Set_Pixel_Sizes(s_data->font, 0, charSize)) LoggerSys::error("Error: freetype cannot set font size: {0}", charSize);

		//Init font texture
		s_data->fontTexture.reset(new OpenGLTexture(s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, 4, nullptr, 0));

		//Fill the glyph buffer
		memset(s_data->glyphBuffer.get(), 60, s_data->glyphBufferSize);

		// Send glyph buffer to the texture on the GPU
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get());

	}

	void Renderer2D::begin(const SceneWideUniforms& sceneWideUniforms){
		// Bind the geometry
		glBindVertexArray(s_data->VAO->getRenderID());

		// Bind the shader
		glUseProgram(s_data->shader->getRenderID());
		
		
		s_data->quadUBO->uploadData("u_view", sceneWideUniforms.at("u_view").second);
		s_data->quadUBO->uploadData("u_projection", sceneWideUniforms.at("u_projection").second);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint){
		Renderer2D::submit(quad, tint, s_data->defaultTexture);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture){
		Renderer2D::submit(quad, s_data->defaultTint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture){

		uint32_t textSlot;
		const uint32_t& textureID = texture->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees){
		Renderer2D::submit(quad, tint, s_data->defaultTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees){
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<OpenGLTexture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		uint32_t textSlot;
		const uint32_t& textureID = texture->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f }), quad.m_scale);

		s_data->shader->uploadFloat4("u_tint", tint);
		s_data->shader->uploadMat4("u_model", s_data->model);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint){
		// Get glyph from freetype
		if (FT_Load_Char(s_data->font, ch, FT_LOAD_RENDER)) LoggerSys::error("Could not load glyph for char {0}", ch);
		else {
			// Get glyph data
			uint32_t glyphWidth = s_data->font->glyph->bitmap.width;
			uint32_t glyphHeight = s_data->font->glyph->bitmap.rows;
			glm::vec2 glyphSize(glyphWidth, glyphHeight);
			glm::vec2 glyphBearing(s_data->font->glyph->bitmap_left, -s_data->font->glyph->bitmap_top);

			// Calculate the advance
			advance = static_cast<float>(s_data->font->glyph->advance.x >> 6);

			// Calculate the quad for the glyph
			glm::vec2 glyphHalfExtents(s_data->fontTexture->getWidthf() * 0.5f, s_data->fontTexture->getHeightf() * 0.5f);
			glm::vec2 glyphCentre = (position + glyphBearing) + glyphHalfExtents;
			Quad quad = Quad::createCentralHalfExtents(glyphCentre, glyphHalfExtents);

			RtoRGBA(s_data->font->glyph->bitmap.buffer, glyphWidth, glyphHeight);
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, s_data->glyphBuffer.get());

			// Sumbit character ( quad )
			submit(quad, tint, s_data->fontTexture);
		}
	}

	void Renderer2D::submit(const char* text, const glm::vec2& position, const glm::vec4& tint){
		uint32_t len = strlen(text);
		float advance = 0.f, x = position.x;

		for (int32_t i = 0; i < len; i++) {
			submit(text[i],{x, position.y}, advance, tint);
			x += advance;
		}
	}

	void Renderer2D::end(){
	}

	void Renderer2D::RtoRGBA(unsigned char* rBuffer, uint32_t width, uint32_t height){

		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize);

		unsigned char* pWalker = s_data->glyphBuffer.get();
		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				*pWalker = 255; pWalker++; // Go to A
				*pWalker = 255; pWalker++;// Go to A
				*pWalker = 255; pWalker++;// Go to A
				*pWalker = *rBuffer; // Set alpha channel
				pWalker++; // Go toR next pixel
				rBuffer++; // Go next monochrome pixel
			}
			pWalker += (s_data->glyphBufferDims.x - width) * 4;
		}
	}

	Quad Quad::createCentralHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents) {
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.0f, 1.0f);

		return result;
	}
}
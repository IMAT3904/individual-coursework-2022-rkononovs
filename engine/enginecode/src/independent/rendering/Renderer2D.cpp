/* \file Renderer2D.cpp */
#include "engine_pch.h"
#include "rendering/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;
	VertexBufferLayout Renderer2DVertex::layout = VertexBufferLayout({ ShaderDataType::Float4, ShaderDataType::Float2, ShaderDataType::FlatInt, {ShaderDataType::Byte4, true} });

	void Renderer2D::init() {
		s_data.reset(new InternalData);

		unsigned char whitePx[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(new OpenGLTexture(1, 1, 4, whitePx, 0));
		s_data->defaultSubTexture.reset(new SubTexture(s_data->defaultTexture, glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)));
		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.0f);

		s_data->textureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

		s_data->shader.reset(new OpenGLShader("./assets/shaders/quad2.glsl"));

		s_data->quad[0] = { -0.5f, -0.5f, 1.f, 1.f };
		s_data->quad[1] = { -0.5f,  0.5f, 1.f, 1.f };
		s_data->quad[2] = {  0.5f,  0.5f, 1.f, 1.f };
		s_data->quad[3] = {  0.5f, -0.5f, 1.f, 1.f };

		//std::array<Renderer2DVertex, 4> vertices;
		s_data->vertices[0] = Renderer2DVertex(s_data->quad[0], {0.f, 0.f}, 0, glm::vec4(1.f));
		s_data->vertices[1] = Renderer2DVertex(s_data->quad[1], {0.f, 1.f}, 0, glm::vec4(1.f));
		s_data->vertices[2] = Renderer2DVertex(s_data->quad[2], {1.f, 1.f}, 0, glm::vec4(1.f));
		s_data->vertices[3] = Renderer2DVertex(s_data->quad[3], {1.f, 0.f}, 0, glm::vec4(1.f));
		/*
		float vertices[4 * 4] = {
			-0.5f, -0.5f, 0.f, 0.f,
			-0.5f,  0.5f, 0.f, 1.f,
			 0.5f,  0.5f, 1.f, 1.f,
			 0.5,  -0.5f, 1.f, 0.f
		};
		*/

		uint32_t indices[4] = { 0,1,2,3 };

		UniformBufferLayout quadLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };
		s_data->quadUBO.reset(new OpenGLUniformBuffer(quadLayout));

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;

		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), Renderer2DVertex::layout));
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
		s_data->fontTexture.reset(new OpenGLTexture(s_data->glyphBufferDims.x, s_data->glyphBufferDims.y, 4, nullptr, 4));

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
		
		s_data->shader->uploadIntArray("u_texData", s_data->textureUnits.data(), 32);
		
		s_data->quadUBO->uploadData("u_view", sceneWideUniforms.at("u_view").second);
		s_data->quadUBO->uploadData("u_projection", sceneWideUniforms.at("u_projection").second);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint){
		Renderer2D::submit(quad, tint, s_data->defaultSubTexture);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<SubTexture>& texture){
		Renderer2D::submit(quad, s_data->defaultTint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<SubTexture>& texture){

		uint32_t textSlot;
		const uint32_t& textureID = texture->getBaseTexture()->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->getBaseTexture()->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);

		//s_data->shader->uploadFloat4("u_tint", tint);
		//s_data->shader->uploadMat4("u_model", s_data->model);
		
		for (int i = 0; i < 4; i++) {
			s_data->vertices[i].position = s_data->model * s_data->quad[i];
			s_data->vertices[i].tint = packedTint;
		}
		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), 0);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees){
		Renderer2D::submit(quad, tint, s_data->defaultSubTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees){
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees)
	{
		if (degrees) angle = glm::radians(angle);

		uint32_t textSlot;
		const uint32_t& textureID = texture->getBaseTexture()->getRenderID();
		bool needsBinding = RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
		if (needsBinding) {
			if (textSlot == -1) {
				RendererCommon::s_textureUnitManager.clear();
				RendererCommon::s_textureUnitManager.getUnit(textureID, textSlot);
			}
			texture->getBaseTexture()->bindToSlot(textSlot);
		}

		s_data->shader->uploadInt("u_texData", textSlot);

		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f }), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);
		//s_data->shader->uploadFloat4("u_tint", tint);

		for (int i = 0; i < 4; i++) {
			s_data->vertices[i].position = s_data->model * s_data->quad[i];
			s_data->vertices[i].tint = packedTint;
		}
		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), 0);

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
			//submit(quad, tint, s_data->fontTexture);
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

	uint32_t Renderer2DVertex::pack(const glm::vec4& tint){
		uint32_t result = 0;
		
		uint32_t r = (static_cast<uint32_t>(tint.r * 255.f)) << 0;
		uint32_t g = (static_cast<uint32_t>(tint.g * 255.f)) << 8;
		uint32_t b = (static_cast<uint32_t>(tint.b * 255.f)) << 16;
		uint32_t a = (static_cast<uint32_t>(tint.a * 255.f)) << 24;

		result = (r | g | b | a);
		return result;
	}
}
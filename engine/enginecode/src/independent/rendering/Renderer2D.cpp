/* \file Renderer2D.cpp */
#include "engine_pch.h"
#include "rendering/Renderer2D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <numeric>

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
		s_data->quad[2] = { 0.5f,  0.5f, 1.f, 1.f };
		s_data->quad[3] = { 0.5f, -0.5f, 1.f, 1.f };

		s_data->vertices.resize(s_data->batchSize);
		s_data->vertices[0] = Renderer2DVertex(s_data->quad[0], { 0.f, 0.f }, 0, glm::vec4(1.f));
		s_data->vertices[1] = Renderer2DVertex(s_data->quad[1], { 0.f, 1.f }, 0, glm::vec4(1.f));
		s_data->vertices[2] = Renderer2DVertex(s_data->quad[2], { 1.f, 1.f }, 0, glm::vec4(1.f));
		s_data->vertices[3] = Renderer2DVertex(s_data->quad[3], { 1.f, 0.f }, 0, glm::vec4(1.f));

		std::vector<uint32_t> indices(s_data->batchSize);
		std::iota(indices.begin(), indices.end(), 0);

		UniformBufferLayout quadLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };
		s_data->quadUBO.reset(new OpenGLUniformBuffer(quadLayout));

		std::shared_ptr<OpenGLVertexBuffer> VBO;
		std::shared_ptr<OpenGLIndexBuffer> IBO;

		s_data->VAO.reset(new OpenGLVertexArray());
		VBO.reset(new OpenGLVertexBuffer(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), Renderer2DVertex::layout));
		IBO.reset(new OpenGLIndexBuffer(indices.data(), indices.size()));

		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->quadUBO->attachShaderBlock(s_data->shader, "b_cameraQuad");

		// Path to font file
		const char* filePath = "./assets/fonts/arial.ttf";

		// Init freetype
		if (FT_Init_FreeType(&s_data->ft)) LoggerSys::error("Error: Freetype could not initialise.");

		// Load font
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->font)) LoggerSys::error("Error: Freetype could not load font: {0}", filePath);

		// Set the char size
		int32_t charSize = 86;
		if (FT_Set_Pixel_Sizes(s_data->font, 0, charSize)) LoggerSys::error("Error: freetype cannot set font size: {0}", charSize);

		//Fill the texture atlas
		s_data->glyphData.resize(s_data->lastGlyph - s_data->firstGlyph + 1);

		for (unsigned ch = s_data->firstGlyph; ch <= s_data->lastGlyph; ch++) {
			if (FT_Load_Char(s_data->font, ch, FT_LOAD_RENDER)) LoggerSys::error("Could not load glyph for char {0}", ch);
			else {
				GlyphData& gd = s_data->glyphData.at(ch - s_data->firstGlyph);
				// Get glyph data
				gd.size = glm::vec2(s_data->font->glyph->bitmap.width, s_data->font->glyph->bitmap.rows);
				gd.bearing = glm::vec2(s_data->font->glyph->bitmap_left, -s_data->font->glyph->bitmap_top);

				// Calculate the advance
				gd.advance = static_cast<float>(s_data->font->glyph->advance.x >> 6);

				//Set the dim of the glyph buffer
				glm::vec2 glyphBufferDims = gd.size;
				uint32_t glyphBufferSize = glyphBufferDims.x * glyphBufferDims.y * 4 * sizeof(unsigned char);

				unsigned char* glyphBuffer = static_cast<unsigned char*>(malloc(glyphBufferSize));

				RtoRGBA(glyphBuffer, s_data->font->glyph->bitmap.buffer, gd.size.x, gd.size.y);
				s_data->glyphAtlas.add(gd.size.x, gd.size.y, 4, glyphBuffer, gd.subTexture);

				free(glyphBuffer);
			}
		}
	}

	void Renderer2D::begin(const SceneWideUniforms& sceneWideUniforms){
		// Reset drawcount
		s_data->drawCount = 0;

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
		if (s_data->drawCount + 4 > s_data->batchSize) flush();
		if (RendererCommon::s_textureUnitManager.full()) flush();
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

		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);

		uint32_t startIdx = s_data->drawCount;
		for (int i = 0; i < 4; i++) {
			s_data->vertices[i + startIdx].position = s_data->model * s_data->quad[i];
			s_data->vertices[i + startIdx].tint = packedTint;
			s_data->vertices[i + startIdx].texUnit = textSlot;
		}

		s_data->vertices[startIdx + 0].uvCoords = texture->getUVStart();
		s_data->vertices[startIdx + 1].uvCoords = { texture->getUVStart().x, texture->getUVEnd().y };
		s_data->vertices[startIdx + 2].uvCoords = texture->getUVEnd();
		s_data->vertices[startIdx + 3].uvCoords = { texture->getUVEnd().x, texture->getUVStart().y };

		s_data->drawCount += 4;
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees){
		Renderer2D::submit(quad, tint, s_data->defaultSubTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees){
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const std::shared_ptr<SubTexture>& texture, float angle, bool degrees)
	{
		if (s_data->drawCount + 4 > s_data->batchSize) flush();
		if (RendererCommon::s_textureUnitManager.full()) flush();

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

		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, {0.f, 0.f, 1.f }), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);

		uint32_t startIdx = s_data->drawCount;
		for (int i = 0; i < 4; i++) {
			s_data->vertices[i + startIdx].position = s_data->model * s_data->quad[i];
			s_data->vertices[i + startIdx].tint = packedTint;
			s_data->vertices[i + startIdx].texUnit = textSlot;
		}

		s_data->vertices[startIdx + 0].uvCoords = texture->getUVStart();
		s_data->vertices[startIdx + 1].uvCoords = { texture->getUVStart().x, texture->getUVEnd().y };
		s_data->vertices[startIdx + 2].uvCoords = texture->getUVEnd();
		s_data->vertices[startIdx + 3].uvCoords = { texture->getUVEnd().x, texture->getUVStart().y };

		s_data->drawCount += 4;
	}

	void Renderer2D::submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint){

		if (ch >= s_data->firstGlyph && ch <= s_data->lastGlyph) {
			GlyphData& gd = s_data->glyphData.at(ch - s_data->firstGlyph);

			advance = gd.advance;
			// Calculate the quad for the glyph
			glm::vec2 glyphHalfExtents(gd.size * 0.5f);
			glm::vec2 glyphCentre = (position + gd.bearing) + glyphHalfExtents;
			Quad quad = Quad::createCentralHalfExtents(glyphCentre, glyphHalfExtents);

			submit(quad, tint, gd.subTexture);
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
		if (s_data->drawCount > 0) flush();
	}

	void Renderer2D::flush() {
		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->drawCount, 0);
		glDrawElements(GL_QUADS, s_data->VAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);

		s_data->drawCount = 0;
	}

	void Renderer2D::RtoRGBA(unsigned char *DSTbuffer, unsigned char* SRCBuffer, uint32_t width, uint32_t height){
		unsigned char* pWalker = DSTbuffer;

		for (int32_t i = 0; i < height; i++) {
			for (int32_t j = 0; j < width; j++) {
				*pWalker = 255; pWalker++; // Go to A
				*pWalker = 255; pWalker++;// Go to A
				*pWalker = 255; pWalker++;// Go to A
				*pWalker = *SRCBuffer; // Set alpha channel
				pWalker++; // Go toR next pixel
				SRCBuffer++; // Go next monochrome pixel
			}
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
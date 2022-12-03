/** OpenGLShader.cpp */

#include "engine_pch.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "systems/loggerSys.h"

#include <string>
#include <array>
#include <fstream>


namespace Engine {
	OpenGLShader::OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath){
		std::string line, vertexSrc, fragmentSrc;

		std::fstream handle(vertexFilepath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { vertexSrc += line; }
		}
		else {
			LoggerSys::error("Could not open vertex shader source: {0}", vertexFilepath);
			return;
		}
		handle.close();


		handle.open(fragmentFilepath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) { fragmentSrc += line; }
		}
		else {
			LoggerSys::error("Could not open vertex shader source: {0}", fragmentFilepath);
			return;
		}
		handle.close();

		compileAndLink(vertexSrc.c_str(), fragmentSrc.c_str());
	}
	OpenGLShader::OpenGLShader(const char* filepath){
		enum Region {None = -1, Vertex = 0, Fragment, Geometry, TessellationControl, TessellationEvaluation, Compute};

		std::string line;
		std::array<std::string, Region::Compute + 1>  src;
		uint32_t region = Region::None;
		
		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open()) {
			while (getline(handle, line)) {
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue; }
				if (line.find("#region Fragment") != std::string::npos) { region = Region::Fragment; continue; }
				if (line.find("#region Geometry") != std::string::npos) { region = Region::Geometry; continue; }
				if (line.find("#region TessellationControl") != std::string::npos) { region = Region::TessellationControl; continue; }
				if (line.find("#region TessellationEvaluation") != std::string::npos) { region = Region::TessellationEvaluation; continue; }
				if (line.find("#region Compute") != std::string::npos) { region = Region::Compute; continue; }

				if(region != Region::None) src[region] += (line + "\n");
			}
		}
		else {
			LoggerSys::error("Could not open vertex shader source: {0}", filepath);
			return;
		}
		handle.close();

		compileAndLink(src[Region::Vertex].c_str(), src[Region::Fragment].c_str());
	}
	OpenGLShader::~OpenGLShader(){
	}
	void OpenGLShader::uploadInt(const char* name, int value){
	}
	void OpenGLShader::uploadFloat(const char* name, float value){
	}
	void OpenGLShader::uploadFloat2(const char* name, const glm::vec2& value){
	}
	void OpenGLShader::uploadFloat3(const char* name, const glm::vec3& value){
	}
	void OpenGLShader::uploadFloat4(const char* name, const glm::vec4& value){
	}
	void OpenGLShader::uploadMat4(const char* name, const glm::mat4& value){
	}
	void OpenGLShader::compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
	}
}
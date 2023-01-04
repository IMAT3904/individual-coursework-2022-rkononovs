/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include "rendering/TextureUnitManager.h"

namespace Engine {
	// Set static vars
	// uint32_t OpenGLTexture::m_textureAmount = 0;
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		// Start logger
		m_loggerSystem.reset(new LoggerSys);
		m_loggerSystem->start();
		
		// Reset and start timer
		m_timer.reset(new MiliTimer);
		m_timerSeconds.reset(new SecondsTimer);

		m_timerSeconds->start();
		m_timer->start();

		// Start the windows system
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		WindowProperties props("My Game Engine", 1044, 800);
		m_window.reset(Window::create(props));

		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMovedCallback(std::bind(&Application::onWindowMoved, this, std::placeholders::_1));
		                                                                                                                                                                                                                                                                             
		m_window->getEventHandler().setOnKeyPressedCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleasedCallback(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyTypedCallback(std::bind(&Application::onKeyTyped, this, std::placeholders::_1));

		m_window->getEventHandler().setOnMouseDownCallback(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseUpCallback(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseWheelCallback(std::bind(&Application::onMouseScrolled, this, std::placeholders::_1));

		InputPoller::setNativeWindow(m_window->getNativeWindow());
	}

	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		m_running = false;
		return e.handled();
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Window resize event: ({0}, {1})", e.getWidth(), e.getHeight());
		return e.handled();
	}

	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Window on focus");
		return e.handled();
	}

	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Window lost focus");
		return e.handled();
	}

	bool Application::onWindowMoved(WindowMovedEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Window moved to: ({0}, {1})", e.getXPos(), e.getYPos());
		return e.handled();
	}

	bool Application::onKeyPressed(KeyPressedEvent& e) {
		e.handle(true);
		//LoggerSys::info("Key pressed event: key: {0}, repeat: {1}", e.getKeyCode(), e.getRepeatCount());
		return e.handled();
	}
	bool Application::onKeyReleased(KeyReleasedEvent& e) {
		e.handle(true);
		//LoggerSys::info("Key released event: key: {0}", e.getKeyCode());
		return e.handled();
	}

	bool Application::onKeyTyped(KeyTypedEvent& e)
	{
		e.handle(true);
		// How to log that? What does typed even do?
		return e.handled();
	}

	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Mouse button {0} pressed", e.getButton());
		return e.handled();
	}

	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Mouse button {0} released", e.getButton());
		return e.handled();
	}

	bool Application::onMouseMoved(MouseMovedEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Mouse moved by {0} x and {1} y.", e.getX(), e.getY());
		return e.handled();
	}

	bool Application::onMouseScrolled(MouseScrolledEvent& e)
	{
		e.handle(true);
		//LoggerSys::info("Mouse scrolled by {0} y.", e.getYOffset());
		return e.handled();
	}

	Application::~Application()
	{
		// Stop logger
		//m_loggerSystem->stop();
		// Stop window system
		m_windowsSystem->stop();
	}


	void Application::run()
	{
#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.f,

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33,  0.f,

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f, 0.f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f,  0.5f,

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.f,   0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.f,   1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f,  0.5f,

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
		};

		float pyramidVertices[6 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
				-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

				-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

				-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
				 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
		std::shared_ptr<OpenGLVertexArray> cubeVAO;
		std::shared_ptr<OpenGLVertexBuffer> cubeVBO;
		std::shared_ptr<OpenGLIndexBuffer> cubeIBO;

		cubeVAO.reset(new OpenGLVertexArray);

		VertexBufferLayout cubeBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(new OpenGLVertexBuffer(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(new OpenGLIndexBuffer(cubeIndices, 36));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		std::shared_ptr<OpenGLVertexArray> pyramidVAO;
		std::shared_ptr<OpenGLVertexBuffer> pyramidVBO;
		std::shared_ptr<OpenGLIndexBuffer> pyramidIBO;

		pyramidVAO.reset(new OpenGLVertexArray);

		VertexBufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };
		pyramidVBO.reset(new OpenGLVertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(new OpenGLIndexBuffer(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);

		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion


#pragma region SHADERS

		std::shared_ptr<OpenGLShader> FCShader;
		FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.glsl"));
		//FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 

#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> letterTexture;
		std::shared_ptr<OpenGLTexture> numberTexture;
		letterTexture.reset(new OpenGLTexture("assets/textures/letterCube.png", 0));
		numberTexture.reset(new OpenGLTexture("assets/textures/numberCube.png", 1));

#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		// Camera UBO
		uint32_t blockNumber = 0;

		UniformBufferLayout camLayout = { { "u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };

		std::shared_ptr<OpenGLUniformBuffer> cameraUBO;
		cameraUBO.reset(new OpenGLUniformBuffer(camLayout));

		cameraUBO->attachShaderBlock(FCShader, "b_camera");
		cameraUBO->attachShaderBlock(TPShader, "b_camera");

		cameraUBO->uploadData("u_projection", glm::value_ptr(projection));
		cameraUBO->uploadData("u_view", glm::value_ptr(view));

		blockNumber++;

		glm::vec3 lightColour(1.f, 1.f, 1.f);
		glm::vec3 lightPos(1.f, 4.f, 6.f);
		glm::vec3 viewPos(0.f, 0.f, 0.f);

		uint32_t lightsUBO;
		uint32_t lightsDataSiz = sizeof(glm::vec4) * 3;

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, lightsDataSiz, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightsUBO, 0, lightsDataSiz);

		uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getRenderID(), "b_lights");
		glUniformBlockBinding(TPShader->getRenderID(), blockIndex, blockNumber);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightColour));

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		TextureUnitManager unitManager(32);
		uint32_t slot;

		float timestep = 0.f;
		float timeSeconds = 0.f;
		int seconds = 0;

		LoggerSys::info("Application is starting.");
		LoggerSys::file("Application is starting. One");
		LoggerSys::file("Application is starting. Two");
		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			timeSeconds = m_timerSeconds->getElapsedTime();

			//if (InputPoller::isKeyPressed(NG_KEY_W)) LoggerSys::error("W has been pressed"); 
			//if (InputPoller::isMouseButtonPressed(NG_MOUSE_BUTTON_1)) LoggerSys::error("Left mouse button has been pressed");

			// Do frame stuff
			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(FCShader->getRenderID());
			glBindVertexArray(pyramidVAO->getRenderID());

			//GLuint uniformLocation;

			FCShader->uploadMat4("u_model", models[0]);

			glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);

			glUseProgram(TPShader->getRenderID());
			glBindVertexArray(cubeVAO->getRenderID());

			TPShader->uploadMat4("u_model", models[1]);;
			if (unitManager.getUnit(letterTexture->getRenderID(), slot)) {
				letterTexture->bindToSlot(slot);
			}
			TPShader->uploadInt("u_textData", slot);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);

			TPShader->uploadMat4("u_model", models[2]);

			if (unitManager.getUnit(numberTexture->getRenderID(), slot)) {
				numberTexture->bindToSlot(slot);
			}
			TPShader->uploadInt("u_textData", slot);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawnCount(), GL_UNSIGNED_INT, nullptr);

			m_window->onUpdate(timestep);
		};
	}

}

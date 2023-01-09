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
#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"
#include "cameras/FreeEulerController.h"
#include "cameras/FollowCamera.h"

namespace Engine {
	// Set static vars
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

		WindowProperties props("My Game Engine", 1024, 800);
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
		if ((InputPoller::isKeyPressed(NG_KEY_TAB) == GLFW_PRESS) && (m_EulerCamera)) {
			m_updatedView = false;
			m_EulerCamera = false;
		}
		else if ((InputPoller::isKeyPressed(NG_KEY_TAB) == GLFW_PRESS)) {
			m_updatedView = false;
			m_EulerCamera = true;
		}
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

		float pyramidVertices[8 * 16] = {
			//	 <------ Pos ------>   <------ normal ------>    <-- UV -->
				-0.5f, -0.5f, -0.5f,    0.f,   -1.f,   0.f,      0.f, 0.5f, //  square Magneta
				 0.5f, -0.5f, -0.5f,    0.f,   -1.f,   0.f,      0.f, 0.5f,
				 0.5f, -0.5f,  0.5f,    0.f,   -1.f,   0.f,      0.33f, 0.5f,
				-0.5f, -0.5f,  0.5f,    0.f,   -1.f,   0.f,      0.33f, 0.f,

				-0.5f, -0.5f, -0.5f,   -0.8944f, 0.4472f, 0.f,   0.f, 0.f,  //triangle Green
				-0.5f, -0.5f,  0.5f,   -0.8944f, 0.4472f, 0.f,   0.f, 0.f,
				 0.0f,  0.5f,  0.0f,   -0.8944f, 0.4472f, 0.f,   0.f, 0.f,

				-0.5f, -0.5f,  0.5f,   0.f, 0.4472f, 0.8944f,    0.f, 0.f,  //triangle Red
				 0.5f, -0.5f,  0.5f,   0.f, 0.4472f, 0.8944f,    0.f, 0.f,
				 0.0f,  0.5f,  0.0f,   0.f, 0.4472f, 0.8944f,    0.f, 0.f,

				 0.5f, -0.5f,  0.5f,   0.8944f, 0.4472f, 0.f,    0.f, 0.f,  //triangle Yellow
				 0.5f, -0.5f, -0.5f,   0.8944f, 0.4472f, 0.f,    0.f, 0.f,
				 0.0f,  0.5f,  0.0f,   0.8944f, 0.4472f, 0.f,    0.f, 0.f,

				 0.5f, -0.5f, -0.5f,   0.f, 0.4472f, -0.8944f,   0.f, 0.f, //triangle Blue
				-0.5f, -0.5f, -0.5f,   0.f, 0.4472f, -0.8944f,   0.f, 0.f,
				 0.0f,  0.5f,  0.0f,   0.f, 0.4472f, -0.8944f,   0.f, 0.f
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

		//VertexBufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		pyramidVBO.reset(new OpenGLVertexBuffer(pyramidVertices, sizeof(pyramidVertices), cubeBL));

		pyramidIBO.reset(new OpenGLIndexBuffer(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);

		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#pragma endregion


#pragma region SHADERS

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 

#pragma region TEXTURES
		std::shared_ptr<OpenGLTexture> letterTexture;
		letterTexture.reset(new OpenGLTexture("./assets/textures/letterCube.png", 0));
		std::shared_ptr<OpenGLTexture> numberTexture;
		numberTexture.reset(new OpenGLTexture("./assets/textures/numberCube.png", 0));
		std::shared_ptr<OpenGLTexture> moonTexture;
		moonTexture.reset(new OpenGLTexture("./assets/textures/moon.png", 0));

		std::shared_ptr<SubTexture> moonSubTexture;
		//SubTexture letterSubTexture(letterTexture, glm::vec2(0.f, 0.f), glm::vec2(1.f, 0.5f));
		//SubTexture numberSubTexture(numberTexture, glm::vec2(0.f, 0.5f), glm::vec2(1.f, 1.f));
		moonSubTexture.reset(new SubTexture(moonTexture, glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)));

#pragma endregion

#pragma region MATERIALS

		std::shared_ptr<Material> pyramidMat;
		std::shared_ptr<Material> letterCubeMat;
		std::shared_ptr<Material> numberCubeMat;

		pyramidMat.reset(new Material(TPShader,{ 0.3f, 0.9f, 4.f, 1.f }));
		letterCubeMat.reset(new Material(TPShader, letterTexture));
		numberCubeMat.reset(new Material(TPShader, numberTexture));

#pragma endregion

#pragma region MODELS
		glm::vec3 positionPlayerCube = glm::vec3(0.f);
		glm::mat4 models[4];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));
		models[3] = glm::translate(glm::mat4(1.0f), positionPlayerCube);
#pragma endregion

#pragma region CAMERAS
		EulerCameraProps camP;
		std::shared_ptr<FreeEulerControllerEuler> camera3DEuler;
		camP.position = glm::vec3(0.f, 0.f, 6.f);
		camP.aspectRation = (float)m_window->getWidth() / (float)m_window->getHeight();
		camera3DEuler.reset(new FreeEulerControllerEuler(camP));
		
		FollowParams camP2;
		std::shared_ptr<FollowCamera> followCamera;
		camP2.entityTransform = &models[3];
		camP2.offset = { 0.f, 1.5f, 5.5f };
		followCamera.reset(new FollowCamera(camP2));

#pragma endregion

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);
		
		glm::vec4 tint(0.3f, 0.9f, 4.f, 1.f);
	
		glm::mat4 view2D = glm::mat4(1.f);
		glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f);

		glm::mat4 cam3Dview = camera3DEuler->getCamera().view;
		glm::mat4 cam3Dprojection = camera3DEuler->getCamera().projection;

		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));

		SceneWideUniforms swu3D;

		
		glm::vec3 lightData[3] = { {1.f, 1.f, 1.f}, {-2.f, 4.f, 6.f}, {0.f, 0.f, 0.f} };

		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(followCamera->getCamera().view)));
		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(followCamera->getCamera().projection)));
		swu3D["u_lightColour"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[0])));
		swu3D["u_lightPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[1])));
		swu3D["u_viewPos"] = std::pair<ShaderDataType, void*>(ShaderDataType::Float3, static_cast<void*>(glm::value_ptr(lightData[2])));

		Quad quads[] = {
			Quad::createCentralHalfExtents({ 60.f, 60.f }, { 50.f, 50.f }),
			Quad::createCentralHalfExtents({ 1024.f - 60.f, 60.f }, { 30.f, 30.f }),
			Quad::createCentralHalfExtents({ 1024.f - 60.f, 800.f - 60.f }, { 50.f, 50.f }),
			Quad::createCentralHalfExtents({ 60.f, 800.f - 60.f }, { 50.f, 50.f }),
			Quad::createCentralHalfExtents({ 512.f, 400.f }, { 50.f, 50.f }),
		};

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		TextureUnitManager unitManager(32);
		uint32_t slot;

		float timestep = 0.f;
		float timeSeconds = 0.f;
		int seconds = 0;

		LoggerSys::info("Application is starting.");

		Renderer3D::init();
		Renderer3D::attachShader(TPShader);

		Renderer2D::init();

		glm::vec3 forward;
		glm::vec3 right;
		float advance;

		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			timeSeconds = m_timerSeconds->getElapsedTime();

			if (m_EulerCamera) {
				if (!m_updatedView) {
					swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(camera3DEuler->getCamera().view)));
					m_updatedView = true;
				}
				else {
					camera3DEuler->onUpdate(timestep);
				}
			}
			else {
				if (!m_updatedView) {
					swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(followCamera->getCamera().view)));
					m_updatedView = true;
				}
				else {
					// PlayerCubeMovement
					if (InputPoller::isKeyPressed(NG_KEY_W)) {
						forward = { -models[3][2][0], -models[3][2][1], -models[3][2][2] };
						positionPlayerCube += forward * 0.05f;
						models[3] = glm::translate(glm::mat4(1.f), positionPlayerCube);
					}
					if (InputPoller::isKeyPressed(NG_KEY_S)) {
						forward = { -models[3][2][0], -models[3][2][1], -models[3][2][2] };
						positionPlayerCube += forward * -0.05f;
						models[3] = glm::translate(glm::mat4(1.f), positionPlayerCube);
					}
					if (InputPoller::isKeyPressed(NG_KEY_A)) {
						right = { -models[3][0][0], -models[3][0][1], -models[3][0][2] };
						positionPlayerCube += right * 0.05f;
						models[3] = glm::translate(glm::mat4(1.f), positionPlayerCube);
					}
					if (InputPoller::isKeyPressed(NG_KEY_D)) {
						right = { -models[3][0][0], -models[3][0][1], -models[3][0][2] };
						positionPlayerCube += right * -0.05f;
						models[3] = glm::translate(glm::mat4(1.f), positionPlayerCube);
					}
					followCamera->onUpdate(timestep);
				}
			}

			// Do frame stuff
			models[0] = glm::rotate(models[0], timestep, glm::vec3(0.f, 1.0, 0.f));
			models[1] = glm::rotate(models[1], timestep, glm::vec3(0.f, 1.0, 0.f));
			models[2] = glm::rotate(models[2], timestep, glm::vec3(0.f, 1.0, 0.f));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			
			glEnable(GL_DEPTH_TEST);
			
			Renderer3D::begin(swu3D);

			Renderer3D::submit(pyramidVAO, pyramidMat, models[0]);
			Renderer3D::submit(cubeVAO, letterCubeMat, models[1]);
			Renderer3D::submit(cubeVAO, numberCubeMat, models[2]);
			Renderer3D::submit(cubeVAO, numberCubeMat, models[3]);

			Renderer3D::end();
			
			
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Renderer2D::begin(swu2D);

			Renderer2D::submit(quads[0], {0.f, 1.f, 1.f, 1.f});
			Renderer2D::submit(quads[1], {0.f, 1.f, 1.f, 1.f}, 45.f, true);
			Renderer2D::submit(quads[2], moonSubTexture);
			Renderer2D::submit(quads[3], {1.f, 1.f, 0.f, 1.f}, moonSubTexture);
			Renderer2D::submit(quads[4], {0.f, 1.f, 1.f, 0.5f}, moonSubTexture);
			Renderer2D::submit("My Game!", { 300.f, 70.f }, { 0.2f, 0.2f, 1.f, 1.f });

			Renderer2D::end();

			m_window->onUpdate(timestep);
		};
	}

}

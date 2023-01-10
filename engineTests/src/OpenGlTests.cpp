#include "OpenGLTests.h"

// Vertex array test
TEST(OpenGL, VertexArrayConstructor) {

	Engine::OpenGLVertexArray vao;

	uint32_t id = vao.getRenderID();

	EXPECT_EQ(id, 1);
}

// Vertex buffer test
TEST(OpenGL, VertexArrayBuffersNull) {

	Engine::OpenGLVertexArray vao;

	uint32_t size = vao.getVertexBuffers().size();

	EXPECT_EQ(size, 0);
}

// Vertex draw count test
TEST(OpenGL, VertexArrayDrawCount) {
	Engine::OpenGLVertexArray vao;

	uint32_t drawCount = vao.getDrawnCount();

	EXPECT_EQ(drawCount, 0);
}

// Index buffer constructor test
TEST(OpenGL, IndexBufferConstructor) {
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

	uint32_t countIBO = 36;

	Engine::OpenGLIndexBuffer ibo(cubeIndices, countIBO);


	int32_t count = ibo.getCount();
	int32_t id = ibo.getRenderID();

	EXPECT_EQ(count, 36);
	EXPECT_EQ(id, 1);
}

// Windows properties test
TEST(OpenGL, WindowPropsConstructor) {
	Engine::WindowProperties e("My game", 1000, 700, true);

	const char* title = e.title;
	int32_t width = e.width;
	int32_t height = e.height;
	bool fullscreen = e.isFullScreen;
	bool vSync = e.isVSync;

	EXPECT_STREQ(title, "My game");
	EXPECT_EQ(width, 1000);
	EXPECT_EQ(height, 700);

	EXPECT_TRUE(fullscreen);
	EXPECT_TRUE(vSync);
}

// Default windows properties constructor test
TEST(OpenGL, WindowDefaultPropsConstructor) {
	Engine::WindowProperties e;

	const char* title = e.title;
	int32_t width = e.width;
	int32_t height = e.height;
	bool fullscreen = e.isFullScreen;
	bool vSync = e.isVSync;

	EXPECT_STREQ(title, "My Window");
	EXPECT_EQ(width, 800);
	EXPECT_EQ(height, 600);

	EXPECT_FALSE(fullscreen);
	EXPECT_TRUE(vSync);
}
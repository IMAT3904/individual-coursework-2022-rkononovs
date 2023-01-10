#include "eventTests.h"

// Window Resize test
TEST(Events, ResizeConstructor) {
	Engine::WindowResizeEvent e(800, 600);

	int32_t width1 = e.getWidth();
	int32_t height1 = e.getHeight();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(width1, 800);
	EXPECT_EQ(height1, 600);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryWindow));

	EXPECT_EQ(type, Engine::EventType::WindowResize);
}

// Window moved test
TEST(Events, MovedConstructor) {
	Engine::WindowMovedEvent e(750, 700);

	int32_t movedX1 = e.getXPos();
	int32_t movedY1 = e.getYPos();
	glm::ivec2 movedPos = e.getPos();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(movedX1, 750);
	EXPECT_EQ(movedY1, 700);
	EXPECT_EQ(movedPos.x, 750);
	EXPECT_EQ(movedPos.y, 700);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryWindow));

	EXPECT_EQ(type, Engine::EventType::WindowMoved);
}

// Window focus test
TEST(Events, FocusConstructor) {
	Engine::WindowFocusEvent e;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryWindow));

	EXPECT_EQ(type, Engine::EventType::WindowFocus);
}

// Window lost focus test
TEST(Events, LostFocusConstructor) {
	Engine::WindowLostFocusEvent e;

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryWindow);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryWindow));

	EXPECT_EQ(type, Engine::EventType::WindowLostFocus);
}

// Key Press test
TEST(Events, KeyPressConstructor) {

	Engine::KeyPressedEvent e(113, 2);

	int32_t keyCode = e.getKeyCode();
	int32_t repeatCount = e.getRepeatCount();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(keyCode, 113);
	EXPECT_EQ(repeatCount, 2);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryKeyboard));

	EXPECT_EQ(type, Engine::EventType::KeyPressed);
}

// Key released
TEST(Events, KeyReleasedConstructor) {

	Engine::KeyReleasedEvent e(113);

	int32_t keyCode = e.getKeyCode();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(keyCode, 113);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryKeyboard));

	EXPECT_EQ(type, Engine::EventType::KeyReleased);
}

// Key typed
TEST(Events, KeyTypedConstructor) {

	Engine::KeyTypedEvent e(113, 2);

	int32_t keyCode = e.getKeyCode();
	int32_t repeatCount = e.getRepeatCount();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(keyCode, 113);
	EXPECT_EQ(repeatCount, 2);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryKeyboard);
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryKeyboard));

	EXPECT_EQ(type, Engine::EventType::KeyType);
}

// Mouse button pressed
TEST(Events, MousePressConstructor) {

	Engine::MouseButtonPressedEvent e(4);

	int32_t buttonCode = e.getButton();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(buttonCode, 4);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);

	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryInput));

	EXPECT_EQ(type, Engine::EventType::MouseButtonPressed);
}

// Mouse button released
TEST(Events, MouseReleaseConstructor) {

	Engine::MouseButtonReleasedEvent e(4);

	int32_t buttonCode = e.getButton();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(buttonCode, 4);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);

	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryInput));

	EXPECT_EQ(type, Engine::EventType::MouseButtonReleased);
}

// Mouse moved test
TEST(Events, MouseMovedConstructor) {
	Engine::MouseMovedEvent e(300, 400);

	int32_t movedX1 = e.getX();
	int32_t movedY1 = e.getY();
	
	glm::ivec2 movedPos = e.getPos();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(movedX1, 300);
	EXPECT_EQ(movedY1, 400);
	EXPECT_EQ(movedPos.x, 300);
	EXPECT_EQ(movedPos.y, 400);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);

	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryInput));

	EXPECT_EQ(type, Engine::EventType::MouseMoved);
}

// Mouse scrolled test
TEST(Events, MouseScrolledConstructor) {
	Engine::MouseScrolledEvent e(50, 25);

	int32_t scrolledXOffset = e.getXOffset();
	int32_t scrolledYOffset = e.getYOffset();

	int32_t cat = e.getCategoryFlags();
	Engine::EventType type = e.getEventType();

	EXPECT_EQ(scrolledXOffset, 50);
	EXPECT_EQ(scrolledYOffset, 25);

	EXPECT_EQ(cat, Engine::EventCategory::EventCategoryMouse | Engine::EventCategory::EventCategoryInput);

	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryMouse));
	EXPECT_TRUE(e.isInCategory(Engine::EventCategory::EventCategoryInput));

	EXPECT_EQ(type, Engine::EventType::MouseScrolled);
}
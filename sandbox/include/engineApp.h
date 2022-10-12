#pragma once

// entry point
#include "include/independent/core/entrypoint.h"
#include "engine.h"

class engineApp : public Engine::Application
{
public:
	engineApp();
	~engineApp() override;
};

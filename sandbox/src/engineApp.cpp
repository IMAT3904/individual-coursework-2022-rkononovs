/** \file engineApp.cpp
*/
#include "engineApp.h"

engineApp::engineApp()
{
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{
	return new engineApp();
}
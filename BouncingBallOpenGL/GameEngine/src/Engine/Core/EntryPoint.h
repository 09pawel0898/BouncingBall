#pragma once
#include "Application.h"

extern std::unique_ptr<Engine::Application> 
	Engine::CreateApplication(void);


int main(int arc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->Run();
	return 0;
}
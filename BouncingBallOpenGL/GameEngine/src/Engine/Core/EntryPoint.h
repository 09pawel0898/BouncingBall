#pragma once

#include "Core.h"

extern std::unique_ptr<Engine::Application> 
	Engine::CreateApplication(void);


int main(int arc, char** argv)
{
	EN_DEBUGMSG("Entry point initialized.");
	auto app = Engine::CreateApplication();
	app->Run();
	return 0;
}
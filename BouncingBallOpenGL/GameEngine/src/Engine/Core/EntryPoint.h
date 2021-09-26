#pragma once
#include "Application.h"

extern std::shared_ptr<En::Application> 
	En::CreateApplication(void);


int main(int arc, char** argv)
{
	auto app = En::CreateApplication();
	app->Run();
	return 0;
}
#pragma once
#include "Application.h"

extern std::shared_ptr<En::Application> 
	En::CreateApplication(void);


int main(void)
{
	En::Application::s_Instance = En::CreateApplication();
	En::Application::s_Instance->Run();
	return 0;
}
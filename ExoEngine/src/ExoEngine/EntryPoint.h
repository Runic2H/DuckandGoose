#pragma once
#include "Application.h"


#ifdef EM_PLATFORM_WINDOWS

extern EM::Application* EM::CreateApplication();

int main(int argc, char* argv[])
{

	EM::Log::Init();
	auto app = EM::CreateApplication();
	app->Run();
	delete app;
}


#endif
#include "empch.h"
#include "Application.h"
#include "Log.h"
#include "Platform/Window/Window.h"

namespace EM {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::SystemInput(System* system)
	{
		m_Systems.SystemIncrement(system);
		system->Init();
	}
	void Application::Run() 
	{

		//Window
		Window* window = new Window;
		window->Init();
		m_Systems.SystemIndex(0, window); //1st layer window


		while (!glfwWindowShouldClose(window->GetWindow()))
		{
			window->Update();
		}

		End();
	}

	

	void Application::End()
	{
		m_Systems.DeleteSystem();
	}

}
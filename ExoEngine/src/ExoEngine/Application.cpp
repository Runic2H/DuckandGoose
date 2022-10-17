/*!*************************************************************************
****
\file			Application.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the main game loop

****************************************************************************
***/
#include "empch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/LevelEditor/LevelEditor.h"
#include "Platform/Graphics/Graphics.h"
#include "ECS/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneViewer.h"

namespace EM {

	ECS ecs;

	Application::Application()
	{
		ecs.Init();
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

		Window* m_window = new Window;
		m_window->Init();
		m_Systems.SystemIndex(0, m_window); //1st layer window
		
		p_Editor->Init(m_window);

		//Graphic* m_graphic = new Graphic;
		//m_graphic->Init();
		//m_Systems.SystemIndex(1, m_graphic);

		Transform transform;
		transform.DeserializeFromFile("PlayerTransform.json");
		ecs.RegisterComponent<Transform>();
		ecs.RegisterComponent<RigidBody>();

		auto mGraphics = ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			ecs.SetSystemSignature<Graphic>(signature);
		}
		mGraphics->Init();

		Entity player = ecs.CreateEntity();
		//ecs.AddComponent(player, Player{});
		ecs.AddComponent<Transform>(player, transform);

		FramePerSec fpschecker;
		fpschecker.InitFrame();

		while (!glfwWindowShouldClose(m_window->GetWindow())) //game loop
		{

			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);
			
			fpschecker.StartFrameCount();

			for (System* system : m_Systems)
			{
				system->Update(Timer::GetInstance().GetGlobalDT());
			}

			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			
			p_Editor->Update();
			p_Editor->Draw();

			fpschecker.EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
		}

		End();
	}


	void Application::End()
	{
		p_Editor->End();
		m_Systems.DeleteSystem();
	}

}
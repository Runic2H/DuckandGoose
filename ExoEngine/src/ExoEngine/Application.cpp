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
#include "ExoEngine/Math/CollisionSystem.h"
#include "ExoEngine/Math/PlayerInput.h"
#include <ExoEngine/Math/PhysicsSystem.h>
#include "ECS/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "Audio/AudioEngine.h"
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
		Timer::GetInstance().GlobalTimeStarter();
		Window* m_window = new Window;
		m_window->Init();
		m_Systems.SystemIndex(0, m_window); //1st layer window
		
		p_Editor->Init(m_window);

		Graphic* m_graphic = new Graphic;
		m_graphic->Init();
		//init audio
		/*CAudioEngine aengine;
		aengine.Init();*/


		m_Systems.SystemIndex(1, m_graphic);

		
		p_Audio->Init();
		p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\DuckandGoose\\Exomata\\Assets\\test.wav", 50.f);

		Transform transform;
		RigidBody rigidbody;
		PlayerIn playerinput;
		transform.DeserializeFromFile("PlayerTransform.json");
		ecs.RegisterComponent<Transform>();
		ecs.RegisterComponent<RigidBody>();
		ecs.RegisterComponent<PlayerIn>();

		auto mGraphics = ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			ecs.SetSystemSignature<Graphic>(signature);
		}
		//mGraphics->Init();

		auto mCollision = ecs.RegisterSystem<CollisionSystem>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			signature.set(ecs.GetComponentType<RigidBody>());
			ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();

		auto pInput = ecs.RegisterSystem<PlayerInput>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			signature.set(ecs.GetComponentType<RigidBody>());
			signature.set(ecs.GetComponentType<PlayerIn>());
			ecs.SetSystemSignature<PlayerInput>(signature);
		}
		pInput->Init();

		auto mPosUpdate = ecs.RegisterSystem<PhysicsSystem>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			signature.set(ecs.GetComponentType<RigidBody>());
			ecs.SetSystemSignature<PhysicsSystem>(signature);
		}
		mPosUpdate->Init();

		Entity player = ecs.CreateEntity();
		//ecs.AddComponent(player, Player{});
		ecs.AddComponent<Transform>(player, transform);
		ecs.AddComponent<RigidBody>(player, rigidbody);
		ecs.AddComponent<PlayerIn>(player, playerinput);

		Entity wall = ecs.CreateEntity();
		ecs.AddComponent<Transform>(wall, transform);
		ecs.AddComponent<RigidBody>(wall, rigidbody);

		FramePerSec::GetInstance().InitFrame();
		
		while (!glfwWindowShouldClose(m_window->GetWindow())) //game loop
		{

			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);
			FramePerSec::GetInstance().StartFrameCount();
			
			p_Audio->Update();

			for (System* system : m_Systems)
			{
				system->Update(Timer::GetInstance().GetGlobalDT());
			}
			
			p_Editor->Update();
			p_Editor->Draw();

			pInput->Update(Timer::GetInstance().GetGlobalDT());
			mCollision->Update(Timer::GetInstance().GetGlobalDT());
			mPosUpdate->Update();
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			Timer::GetInstance().Update(Systems::API);
			FramePerSec::GetInstance().EndFrameCount();
	
		}
		
		End();
	}


	void Application::End()
	{
		p_Editor->End();
		p_Audio->Release();
		m_Systems.DeleteSystem();
	}

}
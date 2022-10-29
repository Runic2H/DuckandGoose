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
#include "Log.h"
#include "Platform/Window/Window.h"
#include "Platform/LevelEditor/LevelEditor.h"
#include "Platform/Graphics/Graphics.h"
#include "ExoEngine/Math/collision_system.h"
#include "ECS/Components/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneManager.h"
#include "Audio/AudioEngine.h"

namespace EM {

	ECS ecs;
	SceneManager SM;

	Application::Application()
	{
		FramePerSec::GetInstance().InitFrame();
		ecs.Init();
		SM.OnInit();
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
		p_Editor->Init(m_window);

		
		p_Audio->Init();
		p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\DuckandGoose\\Exomata\\Assets\\test.wav", 50.f);


		auto mGraphics = ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			signature.set(ecs.GetComponentType<Sprite>());
			ecs.SetSystemSignature<Graphic>(signature);
		}
		mGraphics->Init();

		auto mCollision = ecs.RegisterSystem<CollisionSystem>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
			signature.set(ecs.GetComponentType<RigidBody>());
			ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();

		Entity player = ecs.CreateEntity();
		Sprite sprite;
		sprite.SetColor({ 0.0f,0.0f,0.0f,0.0f });
		sprite.SetTexture("Idle");
		Transform transform;
		ecs.AddComponent<Transform>(player, transform);
		ecs.AddComponent<Sprite>(player, sprite);
		
		
		//SM.DeserializeFromFile("SMTest.json");

		//while(ecs.GetTotalEntities() != MAX_ENTITIES - 1)
		//{
		//	Entity player = ecs.CreateEntity();
		//	if (player % 2)
		//	{
		//		ecs.AddComponent<Transform>(player, transform);
		//	}
		//	else
		//	{
		//		ecs.AddComponent<Transform>(player, transform2);
		//	}
		//	ecs.AddComponent<RigidBody>(player, rigidbody);
		//}


		//Entity playerclone = ecs.CloneEntity(1);
		//ecs.RemoveComponent<Transform>(playerclone);

		//Entity playerclone = ecs.CreateEntity();
		//ecs.AddComponent<Transform>(playerclone, transform);
		//ecs.AddComponent<RigidBody>(playerclone, rigidbody);

		
		while (!glfwWindowShouldClose(m_window->GetWindow())) //game loop
		{
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);
		
			p_Audio->Update();
			p_Editor->Update();
			p_Editor->Draw();
		
			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mCollision->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
	
		}
		
		End();
	}


	void Application::End()
	{
		SM.SerializeToFile("SMTest.json");
		p_Editor->End();
		p_Audio->Release();
		m_Systems.DeleteSystem();
	}

}
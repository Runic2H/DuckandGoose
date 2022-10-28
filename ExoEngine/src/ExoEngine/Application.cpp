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
#include "ExoEngine/Math/collision_system.h"
#include "ECS/Components/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneManager.h"

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
		m_Systems.SystemIndex(0, m_window); //1st layer window
		
		p_Editor->Init(m_window);

		//Graphic* m_graphic = new Graphic;
		//m_graphic->Init();
		//m_Systems.SystemIndex(1, m_graphic);

		Transform transform;
		RigidBody rigidbody;
		Transform transform2;
		transform.DeserializeFromFile("PlayerTransform.json");
		transform2.DeserializeFromFile("WallTransform.json");


		auto mGraphics = ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(ecs.GetComponentType<Transform>());
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

		SM.DeserializeFromFile("SM2.json");

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


		//Entity playerclone = ecs.CloneEntity(player);
		//ecs.RemoveComponent<Transform>(playerclone);

		//Entity playerclone = ecs.CreateEntity();
		//ecs.AddComponent<Transform>(playerclone, transform);
		//ecs.AddComponent<RigidBody>(playerclone, rigidbody);

		
		while (!glfwWindowShouldClose(m_window->GetWindow())) //game loop
		{

			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);
			FramePerSec::GetInstance().StartFrameCount();
			
			//if (p_Input->isKeyPressed(GLFW_KEY_UP))
			//	ecs.GetComponent<Transform>(player).GetPos().y += 1 * Timer::GetInstance().GetGlobalDT();
			//if (p_Input->isKeyPressed(GLFW_KEY_DOWN))
			//	ecs.GetComponent<Transform>(player).GetPos().y -= 1 * Timer::GetInstance().GetGlobalDT();
			//if (p_Input->isKeyPressed(GLFW_KEY_RIGHT))
			//	ecs.GetComponent<Transform>(player).GetPos().x += 1 * Timer::GetInstance().GetGlobalDT();
			//if (p_Input->isKeyPressed(GLFW_KEY_LEFT))
			//	ecs.GetComponent<Transform>(player).GetPos().x -= 1 * Timer::GetInstance().GetGlobalDT();

			/*for (System* system : m_Systems)
			{
				system->Update(Timer::GetInstance().GetGlobalDT());
			}*/

			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mCollision->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			
			p_Editor->Update();
			p_Editor->Draw();
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
	
		}
		
		End();
	}


	void Application::End()
	{
		SM.SerializeToFile("SMTest.json");
		p_Editor->End();
		m_Systems.DeleteSystem();
	}

}
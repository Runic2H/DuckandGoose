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
#include "Platform/Physics/CollisionSystem.h"
#include "Platform/InputHandler/PlayerInput.h"
#include "Platform/Physics/PhysicsSystem.h"
#include "ECS/Components/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneManager.h"
#include "Audio/AudioEngine.h"


namespace EM {

	Application::Application()
	{
		p_ecs.Init();
		p_Scene->Init();
		FramePerSec::GetInstance().InitFrame();
	}

	Application::~Application()
	{
	}

	void Application::SystemInput(System* system)
	{
		(void)system;
	}

	void Application::Run() 
	{
		Timer::GetInstance().GlobalTimeStarter();
		
		Window* m_window = new Window;
		m_window->Init();
		p_Editor->Init(m_window);

		
		p_Audio->Init();
		//p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\DuckandGoose\\Exomata\\Assets\\test.wav", 50.f);


		auto mGraphics = p_ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<Sprite>());
			p_ecs.SetSystemSignature<Graphic>(signature);
		}
		mGraphics->Init();

		auto mPlayerInput = p_ecs.RegisterSystem<PlayerInput>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			signature.set(p_ecs.GetComponentType<NameTag>());
			p_ecs.SetSystemSignature<PlayerInput>(signature);
		}
		mPlayerInput->Init();

		auto mPosUpdate = p_ecs.RegisterSystem<PhysicsSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			p_ecs.SetSystemSignature<PhysicsSystem>(signature);
		}
		mPosUpdate->Init();

		auto mCollision = p_ecs.RegisterSystem<CollisionSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			signature.set(p_ecs.GetComponentType<Collider>());
			p_ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();
		
		Entity player = p_ecs.CreateEntity();
		p_ecs.AddComponent<Transform>(player, TransformComponent);
		p_ecs.AddComponent<NameTag>(player, NameTagComponent);
		p_ecs.AddComponent<Collider>(player, ColliderComponent);
		p_ecs.AddComponent<Sprite>(player, SpriteComponent);
		p_ecs.AddComponent<RigidBody>(player, RigidBodyComponent);
		p_ecs.GetComponent<RigidBody>(player).SetVel(0.005f,0.005f);

		Entity enemy = p_ecs.CreateEntity();
		p_ecs.AddComponent<Transform>(enemy, TransformComponent);
		p_ecs.AddComponent<Collider>(enemy, ColliderComponent);
		p_ecs.AddComponent<Sprite>(enemy, SpriteComponent);
		p_ecs.AddComponent<RigidBody>(enemy, RigidBodyComponent);
		//SM.DeserializeFromFile("SMTest.json");


		/*while(p_ecs.GetTotalEntities() != MAX_ENTITIES - 1)
		{
			Entity player = p_ecs.CreateEntity();
			if (player % 2)
			{
				p_ecs.AddComponent<Transform>(player, TransformComponent);
				p_ecs.AddComponent<NameTag>(player, NameTagComponent);
				p_ecs.AddComponent<Collider>(player, ColliderComponent);
				p_ecs.AddComponent<Sprite>(player, SpriteComponent);
			}
			else
			{
				Transform transform;
				p_ecs.AddComponent<Transform>(player, transform);
				p_ecs.AddComponent<Collider>(player, ColliderComponent);
				p_ecs.AddComponent<Sprite>(player, SpriteComponent);
			}
			p_ecs.AddComponent<RigidBody>(player, RigidBodyComponent);
		}*/
		
		
		while (!glfwWindowShouldClose(m_window->GetWindow())) //game loop
		{
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);
		
			p_Audio->Update();
			p_Editor->Update();
			p_Editor->Draw();
		
			m_window->Update(Timer::GetInstance().GetGlobalDT());
			//update input
			mPlayerInput->Update(Timer::GetInstance().GetGlobalDT());
			//update enemies
			
			//run collision calculations
			mCollision->Update(Timer::GetInstance().GetGlobalDT());
			//update positions
			mPosUpdate->Update();
			//render graphics
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
		}
		
		End();
	}


	void Application::End()
	{
		p_Scene->SerializeToFile("SMTest.json");
		p_Editor->End();
		p_Audio->Release();
	}

}
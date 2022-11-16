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
#include "Platform/Physics/PhysicsSystem.h"
#include "ECS/Components/Components.h"
#include "Timer/Time.h"
#include "Timer/Fps.h"
#include "ECS/ECS.h"
#include "ECS/SceneManager.h"
#include "Audio/AudioEngine.h"
#include "ExoEngine/Scripts/PlayerMovement.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "Platform/Logic/LogicSystem.h"
#include "ExoEngine//Scripts/EnemyMovement.h"
#include "ExoEngine/GUI/GUI.h"


namespace EM {
	bool end_state{false}; //placeholder
	Application::Application()
	{
		p_ecs.Init();
		p_Scene->Init();
		//p_Scene->DeserializeFromFile("SMTest.json");
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
		p_Audio->Init();
		p_Editor->Init(m_window);

		
		//p_GUI->gui_init();
		//p_Audio->PlaySound("C:\\Users\\mattc\\Downloads\\DuckandGoose\\Exomata\\Assets\\test.wav", 50.f);

		auto mGraphics = p_ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<Sprite>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			signature.set(p_ecs.GetComponentType<Collider>());
			p_ecs.SetSystemSignature<Graphic>(signature);
		}
		mGraphics->Init();

		auto mPosUpdate = p_ecs.RegisterSystem<PhysicsSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			p_ecs.SetSystemSignature<PhysicsSystem>(signature);
		}
		mPosUpdate->Init();

		auto mLogic = p_ecs.RegisterSystem<LogicSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Logic>());
			p_ecs.SetSystemSignature<LogicSystem>(signature);
		}
		mLogic->Init();

		auto mCollision = p_ecs.RegisterSystem<CollisionSystem>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<Collider>());
			p_ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();

		p_Scene->DeserializeFromFile("Level2.json");

		//p_ecs.DestroyEntity(0);

		//Entity player = p_ecs.CreateEntity();
		//RigidBody rb;
		//Logic logic;
		//Sprite sprite;
		//NameTag name;
		//Player playerID;
		//name.SetNameTag("Player");
		//sprite.SetTexture("Idle");
		//logic.InsertScript(new PlayerMovement(), player);
		//p_ecs.AddComponent<Transform>(player, TransformComponent);
		//p_ecs.AddComponent<RigidBody>(player, rb);
		//p_ecs.AddComponent<Sprite>(player, sprite);
		//p_ecs.AddComponent<NameTag>(player, name);
		//p_ecs.AddComponent<Collider>(player, ColliderComponent);
		//Entity enemy = p_ecs.CloneEntity(player);
		//p_ecs.GetComponent<NameTag>(enemy).SetNameTag("Enemy");
		//p_ecs.AddComponent<Player>(player, playerID);
		//p_ecs.AddComponent<Logic>(player, logic);	//Add Component

		//Logic logic2;
		//logic2.InsertScript(new EnemyMovement(), enemy);
		//p_ecs.AddComponent<Logic>(enemy, logic2);
		
		while (!glfwWindowShouldClose(m_window->GetWindow()) && end_state == false) //game loop
		{
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);

			if (p_GUI->check_pause() == false)
			{
				p_Audio->Update();
				p_Editor->Update();
				p_Editor->Draw();
				
				mLogic->Update(Timer::GetInstance().GetGlobalDT());
				mPosUpdate->Update();
				mCollision->Update(Timer::GetInstance().GetGlobalDT());
			}
			end_state = p_GUI->Update(m_window);

			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
		
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
			
		}
		mLogic->End();
		End();
	}


	void Application::End()
	{
		p_Scene->SerializeToFile("Level.json");
		p_Editor->End();
		p_Audio->Release();
	}
}
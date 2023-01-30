/*!*************************************************************************
****
\file			Application.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			9-28-2022
\brief			This file contain the main game loop

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
#include "ExoEngine/Scripts/PlayerController.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "ExoEngine/Scripts/ButtonResponse.h"
#include "ExoEngine/Scripts/ScenerioScript.h"
#include "Platform/Logic/LogicSystem.h"
#include "ExoEngine/Scripts/EnemyMovement.h"
#include "ExoEngine/GUI/GUI.h"


namespace EM {
	bool end_state{false}; //placeholder

/*!*************************************************************************
Application constructor
****************************************************************************/
	Application::Application()
	{
		p_ecs.Init();
		p_Scene->Init();
		FramePerSec::GetInstance().InitFrame();
	}

/*!*************************************************************************
Application destructor
****************************************************************************/
	Application::~Application()
	{
	}

/*!*************************************************************************
System input
****************************************************************************/
	void Application::SystemInput(System* system)
	{
		(void)system;
	}

/*!*************************************************************************
Run loop for application
****************************************************************************/
	void Application::Run() 
	{
		Timer::GetInstance().GlobalTimeStarter();
		
		Window* m_window = new Window;
		m_window->Init();
		p_Audio->Init();
		p_Editor->Init(m_window);

		auto mGraphics = p_ecs.RegisterSystem<Graphic>();
		{
			Signature signature;
			signature.set(p_ecs.GetComponentType<Transform>());
			signature.set(p_ecs.GetComponentType<Sprite>());
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
			signature.set(p_ecs.GetComponentType<RigidBody>());
			signature.set(p_ecs.GetComponentType<Collider>());
			signature.set(p_ecs.GetComponentType<RigidBody>());
			p_ecs.SetSystemSignature<CollisionSystem>(signature);
		}
		mCollision->Init();

		//FOR DEBUGGING ECS 
		//Scene Manager Requires some tweaking to entity serialization and deserialization
		//RigidBody rb;
		//Logic logic;
		//Sprite sprite;
		//NameTag name;
		//Tag tag;

		//Entity Background = p_ecs.CreateEntity();
		//name.SetNameTag("Main Menu BackGround");
		//p_ecs.AddComponent<NameTag>(Background, name);
		//p_ecs.AddComponent<Transform>(Background, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Background, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Background, rb);
		////p_ecs.AddComponent<Collider>(Background, C_ColliderComponent);
		////p_ecs.AddComponent<Tag>(Background, C_TagComponent);
		////p_ecs.AddComponent<Logic>(Background, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Background).SetPos(0.0f,0.0f);
		//p_ecs.GetComponent<Transform>(Background).SetScale({ 4.170206546783447f,1.9999960660934448f});
		//p_ecs.GetComponent<Sprite>(Background).SetTexture("MainBackGround");

		//Entity Title = p_ecs.CreateEntity();
		//name.SetNameTag("Title");
		//p_ecs.AddComponent<NameTag>(Title, name);
		//p_ecs.AddComponent<Transform>(Title, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Title, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Title, rb);
		////p_ecs.AddComponent<Collider>(Title, C_ColliderComponent);
		////p_ecs.AddComponent<Tag>(Title, C_TagComponent);
		////p_ecs.AddComponent<Logic>(Title, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Title).SetPos({ 0.6422932744026184f,0.43617022037506104f });
		//p_ecs.GetComponent<Transform>(Title).SetScale(1.9796679019927979f, 0.9862148761749268f);
		//p_ecs.GetComponent<Sprite>(Title).SetTexture("ExomataLogo");
		////p_ecs.GetComponent<Logic>(Title).InsertScript(new EnemyMovement(), Title);
		////p_ecs.GetComponent<Logic>(Title).InsertScript(new CollisionResponse(), Title);

		//Entity Title2 = p_ecs.CreateEntity();
		//name.SetNameTag("Title2");
		//p_ecs.AddComponent<NameTag>(Title2, name);
		//p_ecs.AddComponent<Transform>(Title2, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Title2, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Title, rb);
		////p_ecs.AddComponent<Collider>(Title, C_ColliderComponent);
		////p_ecs.AddComponent<Tag>(Title, C_TagComponent);
		////p_ecs.AddComponent<Logic>(Title, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Title2).SetPos({ 0.6422932744026184f,0.43617022037506104f });
		//p_ecs.GetComponent<Transform>(Title2).SetScale(1.9796679019927979f, 0.9862148761749268f);
		//p_ecs.GetComponent<Sprite>(Title2).SetTexture("ExomataLogo");

		/////*Entity Start = p_ecs.CreateEntity();
		////name.SetNameTag("Start");
		////p_ecs.AddComponent<NameTag>(Start, name);
		////p_ecs.AddComponent<Transform>(Start, C_TransformComponent);
		////p_ecs.AddComponent<Sprite>(Start, C_SpriteComponent);
		////p_ecs.AddComponent<Tag>(Start, C_TagComponent);
		////p_ecs.AddComponent<Logic>(Start, C_LogicComponent);
		////p_ecs.GetComponent<Transform>(Start).SetPos({ 0.0f,0.0f });
		////p_ecs.GetComponent<Transform>(Start).SetScale(0.6f, 0.2f);
		////p_ecs.GetComponent<Sprite>(Start).SetTexture("SmallButton");
		////p_ecs.GetComponent<Tag>(Start).SetTag("Start");
		////p_ecs.GetComponent<Logic>(Start).InsertScript(new ButtonResponse(), Start);*/

		//Entity Start = p_ecs.CreateEntity();
		//name.SetNameTag("Start");
		//p_ecs.AddComponent<NameTag>(Start, name);
		//p_ecs.AddComponent<Transform>(Start, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Start, C_SpriteComponent);
		////	p_ecs.AddComponent<RigidBody>(Start, rb);
		//p_ecs.AddComponent<Collider>(Start, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(Start, C_TagComponent);
		//p_ecs.AddComponent<Logic>(Start, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Start).SetPos({ 0.0f,0.0f });
		//p_ecs.GetComponent<Transform>(Start).SetScale(0.6f, 0.2f);
		//p_ecs.GetComponent<Sprite>(Start).SetTexture("SmallButton");
		//p_ecs.GetComponent<Tag>(Start).SetTag("Start");
		//p_ecs.GetComponent<Collider>(Start)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(Start)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(Start).InsertScript(new ButtonResponse(), Start);

		//Entity Quit = p_ecs.CreateEntity();
		//name.SetNameTag("Quit");
		//p_ecs.AddComponent<NameTag>(Quit, name);
		//p_ecs.AddComponent<Transform>(Quit, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Quit, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Quit, rb);
		//p_ecs.AddComponent<Collider>(Quit, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(Quit, C_TagComponent);
		//p_ecs.AddComponent<Logic>(Quit, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Quit).SetPos({ 0.599f,-0.27f });
		//p_ecs.GetComponent<Transform>(Quit).SetScale(0.6f, 0.2f);
		//p_ecs.GetComponent<Sprite>(Quit).SetTexture("SmallButton");
		//p_ecs.GetComponent<Tag>(Quit).SetTag("Quit");
		//p_ecs.GetComponent<Collider>(Quit)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(Quit)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(Quit).InsertScript(new ButtonResponse(), Quit);

		//Entity Option = p_ecs.CreateEntity();
		//name.SetNameTag("Option");
		//p_ecs.AddComponent<NameTag>(Option, name);
		//p_ecs.AddComponent<Transform>(Option, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Option, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Option, rb);
		//p_ecs.AddComponent<Collider>(Option, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(Option, C_TagComponent);
		//p_ecs.AddComponent<Logic>(Option, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Option).SetPos({ 1.165f,-0.563f });
		//p_ecs.GetComponent<Transform>(Option).SetScale(0.6f, 0.2f);
		//p_ecs.GetComponent<Sprite>(Option).SetTexture("SmallButton");
		//p_ecs.GetComponent<Tag>(Option).SetTag("Option");
		//p_ecs.GetComponent<Collider>(Option)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(Option)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(Option).InsertScript(new ButtonResponse(), Option);




		//Entity player = p_ecs.CreateEntity();
		//name.SetNameTag("Player");
		//sprite.SetTexture("Idle");
		//p_ecs.AddComponent<Transform>(player, C_TransformComponent);
		//p_ecs.AddComponent<RigidBody>(player, rb);
		//p_ecs.AddComponent<Sprite>(player, sprite);
		//p_ecs.AddComponent<NameTag>(player, name);
		//p_ecs.AddComponent<Collider>(player, C_ColliderComponent);
		//tag.SetTag("Player");
		//p_ecs.AddComponent<Tag>(player, tag);
		//p_ecs.AddComponent<Logic>(player, logic);	//Add Component
		//p_ecs.GetComponent<Logic>(player).InsertScript(new PlayerController(), player);
		//p_ecs.GetComponent<Logic>(player).InsertScript(new CollisionResponse(), player);
		//Entity enemy = p_ecs.CreateEntity();
		//Logic logic2;
		//p_ecs.AddComponent<Transform>(enemy, C_TransformComponent);
		//p_ecs.AddComponent<RigidBody>(enemy, rb);
		//p_ecs.AddComponent<Sprite>(enemy, sprite);
		//p_ecs.AddComponent<Collider>(enemy, C_ColliderComponent);
		/*p_ecs.AddComponent<Tag>(enemy, C_TagComponent);
		p_ecs.AddComponent<NameTag>(enemy, C_NameTagComponent);
		p_ecs.GetComponent<NameTag>(enemy).SetNameTag("Enemy");
		p_ecs.AddComponent<Logic>(enemy, logic2);
		p_ecs.GetComponent<Logic>(enemy).InsertScript(new EnemyMovement(), enemy);
		p_ecs.GetComponent<Logic>(enemy).InsertScript(new CollisionResponse(), enemy);
		Entity col = p_ecs.CreateEntity();
		p_ecs.AddComponent<Tag>(col, C_TagComponent);
		p_ecs.GetComponent<Tag>(col).SetTag("PlayerAttack");
		p_ecs.GetComponent<Tag>(col).SetTargetTag("Enemy");
		p_ecs.AddComponent<Sprite>(col, C_SpriteComponent);
		p_ecs.AddComponent<Transform>(col, C_TransformComponent);
		p_ecs.GetComponent<Transform>(col).SetComponentEntityID(player);
		p_ecs.GetComponent<Transform>(col).GetComponentEntityID();
		p_ecs.AddComponent<RigidBody>(col, rb);
		p_ecs.AddComponent<NameTag>(col, name);
		p_ecs.GetComponent<NameTag>(col).SetNameTag("PlayerAttackCollider");
		p_ecs.AddComponent<Collider>(col, C_ColliderComponent);
		p_ecs.AddComponent<Logic>(col, C_LogicComponent);*/
		
		//p_Scene->DeserializeFromFile("Assets/Scene/MainMenu.json");
		//p_Editor->is_ShowWindow = false;

		while (!glfwWindowShouldClose(m_window->GetWindow()) && end_state == false) //game loop
		{
			//std::cout << p_GUI->Check_script();
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);

			if (p_GUI->check_pause() == false)
			{
				p_Audio->Update();
				p_Editor->Update();
				if (p_Editor->is_ShowWindow)
				{
					p_Editor->Draw();
				}
				mLogic->Update(Timer::GetInstance().GetGlobalDT());
				mPosUpdate->Update();
				mCollision->Update(Timer::GetInstance().GetGlobalDT());
			}
			end_state = p_GUI->Update(m_window);

			// test menu script
			p_Scene->checkForSceneToLoad();

			p_Input->ResetPressedKey();//to fix the buggy error from glfwpollevent

			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
		
			
			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
			
		}
		mLogic->End();
		End();
	}

/*!*************************************************************************
End loop for application
****************************************************************************/
	void Application::End()
	{
		//p_Scene->SerializeToFile("Assets/Scene/MainMenuTest.json");
		p_Editor->End();
		p_Audio->Release();
	}
}
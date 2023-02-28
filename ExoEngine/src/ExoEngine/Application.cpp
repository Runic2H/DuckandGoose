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
#include "ExoEngine/Scripts/HUDController.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "ExoEngine/Scripts/ButtonResponse.h"
#include "ExoEngine/Scripts/ScenerioScript.h"
#include "ExoEngine/Scripts/AudioManager.h"
#include "Platform/Logic/LogicSystem.h"
#include "ExoEngine/Scripts/EnemyMovement.h"
#include "ExoEngine/Scripts/PlayerControl.h"
#include "ExoEngine/GUI/GUI.h"
#include <stdlib.h>

namespace EM {
	bool end_state{false}; //placeholder

/*!*************************************************************************
Application constructor
****************************************************************************/
	Application::Application()
	{
		_set_abort_behavior(0, _CALL_REPORTFAULT);
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
		//FOR DEBUGGING ECS 
		//Scene Manager Requires some tweaking to entity serialization and deserialization
		RigidBody rb;
		Logic logic;
		Sprite sprite;
		NameTag name;
		Tag tag;

		/*Entity Background = p_ecs.CreateEntity();
		name.SetNameTag("Main Menu BackGround");
		p_ecs.AddComponent<NameTag>(Background, name);
		p_ecs.AddComponent<Transform>(Background, C_TransformComponent);
		p_ecs.AddComponent<Sprite>(Background, C_SpriteComponent);
		p_ecs.AddComponent<RigidBody>(Background, rb);
		p_ecs.AddComponent<Collider>(Background, C_ColliderComponent);
		p_ecs.AddComponent<Tag>(Background, C_TagComponent);
		p_ecs.AddComponent<Logic>(Background, C_LogicComponent);
		p_ecs.AddComponent<Audio>(Background, C_AudioComponent);
		p_ecs.AddComponent<Attributes>(Background, C_AttributesComponent);
		Audio::AudioPiece pce;
		pce.mAudioPath = "Assets/metadigger/HeroFightBossMusic.wav";
		pce.mChannelGroup = Audio::AudioType::BGM;
		pce.mChannel = 0;
		pce.is_Looping = true;
		pce.is_Playing = false;
		pce.should_play = false;
		pce.should_stop = false;
		std::vector<Audio::AudioPiece> ins;
		ins.push_back(pce);
		p_ecs.GetComponent<Audio>(Background).SetArr(ins);
		p_ecs.GetComponent<Logic>(Background).InsertScript(new AudioManager(), Background);
		p_ecs.GetComponent<Transform>(Background).SetPos(0.0f,0.0f);
		p_ecs.GetComponent<Transform>(Background).SetScale({ 4.170206546783447f,1.9999960660934448f});*/

		//Entity hud = p_ecs.CreateEntity();
		//p_ecs.AddComponent<Transform>(hud, C_TransformComponent);
		//p_ecs.GetComponent<Transform>(hud).SetScale(1.f, 0.55f);
		//p_ecs.AddComponent<HUDComponent>(hud, C_HUDComponent);
		//p_ecs.GetComponent<HUDComponent>(hud).SetOffset(vec2D(-1.f, 0.75f));
		//p_ecs.GetComponent<HUDComponent>(hud).SetType(HUDComponent::ElementType::Static);
		//p_ecs.AddComponent<Tag>(hud, C_TagComponent);
		//p_ecs.AddComponent<Sprite>(hud, sprite);
		//p_ecs.GetComponent<Sprite>(hud).SetTexture("HPStatic");
		//p_ecs.AddComponent<Attributes>(hud, C_AttributesComponent);
		//p_ecs.AddComponent<NameTag>(hud, C_NameTagComponent);
		//p_ecs.GetComponent<NameTag>(hud).SetNameTag("HUD");
		//p_ecs.AddComponent<Logic>(hud, logic);
		//p_ecs.GetComponent<Logic>(hud).InsertScript(new HUDController(), hud);

		//Entity hpbar = p_ecs.CreateEntity();
		//p_ecs.AddComponent<Transform>(hpbar, C_TransformComponent);
		//p_ecs.GetComponent<Transform>(hpbar).SetScale(0.75f, 0.15f);
		//p_ecs.AddComponent<HUDComponent>(hpbar, C_HUDComponent);
		//p_ecs.GetComponent<HUDComponent>(hpbar).SetOffset(vec2D(-0.8f, 0.84f));
		//p_ecs.GetComponent<HUDComponent>(hpbar).SetType(HUDComponent::ElementType::HealthBar);
		//p_ecs.AddComponent<Tag>(hpbar, C_TagComponent);
		//p_ecs.AddComponent<Sprite>(hpbar, sprite);
		//p_ecs.GetComponent<Sprite>(hpbar).SetTexture("HPBar");
		//p_ecs.AddComponent<Attributes>(hpbar, C_AttributesComponent);
		//p_ecs.GetComponent<Attributes>(hpbar).SetHealth(100);
		//p_ecs.AddComponent<NameTag>(hpbar, C_NameTagComponent);
		//p_ecs.GetComponent<NameTag>(hpbar).SetNameTag("HPBar");
		//p_ecs.AddComponent<Logic>(hpbar, logic);
		//p_ecs.GetComponent<Logic>(hpbar).InsertScript(new HUDController(), hpbar);
    
		////Entity Option = p_ecs.CreateEntity();
		////name.SetNameTag("Option");
		////p_ecs.AddComponent<NameTag>(Option, name);
		////p_ecs.AddComponent<Transform>(Option, C_TransformComponent);
		////p_ecs.AddComponent<Sprite>(Option, C_SpriteComponent);
		//////p_ecs.AddComponent<RigidBody>(Option, rb);
		////p_ecs.AddComponent<Collider>(Option, C_ColliderComponent);
		////p_ecs.AddComponent<Tag>(Option, C_TagComponent);
		////p_ecs.AddComponent<Logic>(Option, C_LogicComponent);
		////p_ecs.GetComponent<Transform>(Option).SetPos({ 1.165f,-0.563f });
		////p_ecs.GetComponent<Transform>(Option).SetScale(0.6f, 0.2f);
		////p_ecs.GetComponent<Sprite>(Option).SetTexture("SmallButton");
		////p_ecs.GetComponent<Tag>(Option).SetTag("Option");
		////p_ecs.GetComponent<Collider>(Option)[0].mMax = { 0.5,0.5 };
		////p_ecs.GetComponent<Collider>(Option)[0].mMin = { -0.5,-0.5 };
		////p_ecs.GetComponent<Logic>(Option).InsertScript(new ButtonResponse(), Option);
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
		//p_ecs.GetComponent<Transform>(Start).SetScale(1.0f, 0.2f);
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
		//p_ecs.GetComponent<Transform>(Quit).SetPos({ 0.0f,-0.25f });
		//p_ecs.GetComponent<Transform>(Quit).SetScale(1.0f, 0.2f);
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

		/*Entity hud = p_ecs.CreateEntity();
		p_ecs.AddComponent<Transform>(hud, C_TransformComponent);
		p_ecs.GetComponent<Transform>(hud).SetScale(1.f, 0.55f);
		p_ecs.AddComponent<HUDComponent>(hud, C_HUDComponent);
		p_ecs.GetComponent<HUDComponent>(hud).SetOffset(vec2D(-1.f, 0.75f));
		p_ecs.GetComponent<HUDComponent>(hud).SetType(HUDComponent::ElementType::Static);
		p_ecs.AddComponent<Tag>(hud, C_TagComponent);
		p_ecs.AddComponent<Sprite>(hud, sprite);
		p_ecs.GetComponent<Sprite>(hud).SetTexture("HPStatic");
		p_ecs.AddComponent<Attributes>(hud, C_AttributesComponent);
		p_ecs.AddComponent<NameTag>(hud, C_NameTagComponent);
		p_ecs.GetComponent<NameTag>(hud).SetNameTag("HUD");
		p_ecs.AddComponent<Logic>(hud, logic);
		p_ecs.GetComponent<Logic>(hud).InsertScript(new HUDController(), hud);

		Entity hpbar = p_ecs.CreateEntity();
		p_ecs.AddComponent<Transform>(hpbar, C_TransformComponent);
		p_ecs.GetComponent<Transform>(hpbar).SetScale(0.75f, 0.15f);
		p_ecs.AddComponent<HUDComponent>(hpbar, C_HUDComponent);
		p_ecs.GetComponent<HUDComponent>(hpbar).SetOffset(vec2D(-0.8f, 0.84f));
		p_ecs.GetComponent<HUDComponent>(hpbar).SetType(HUDComponent::ElementType::HealthBar);
		p_ecs.AddComponent<Tag>(hpbar, C_TagComponent);
		p_ecs.AddComponent<Sprite>(hpbar, sprite);
		p_ecs.GetComponent<Sprite>(hpbar).SetTexture("HPBar");
		p_ecs.AddComponent<Attributes>(hpbar, C_AttributesComponent);
		p_ecs.GetComponent<Attributes>(hpbar).SetHealth(100);
		p_ecs.AddComponent<NameTag>(hpbar, C_NameTagComponent);
		p_ecs.GetComponent<NameTag>(hpbar).SetNameTag("HPBar");
		p_ecs.AddComponent<Logic>(hpbar, logic);
		p_ecs.GetComponent<Logic>(hpbar).InsertScript(new HUDController(), hpbar);*/

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
		//p_ecs.GetComponent<Transform>(Start).SetScale(1.0f, 0.2f);
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
		//p_ecs.GetComponent<Transform>(Quit).SetPos({ 0.0f,-0.25f });
		//p_ecs.GetComponent<Transform>(Quit).SetScale(1.0f, 0.2f);
		//p_ecs.GetComponent<Sprite>(Quit).SetTexture("SmallButton");
		//p_ecs.GetComponent<Tag>(Quit).SetTag("Quit");
		//p_ecs.GetComponent<Collider>(Quit)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(Quit)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(Quit).InsertScript(new ButtonResponse(), Quit);

		//Entity Option = p_ecs.CreateEntity();
		//name.SetNameTag("Options");
		//p_ecs.AddComponent<NameTag>(Option, name);
		//p_ecs.AddComponent<Transform>(Option, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Option, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(Option, rb);
		//p_ecs.AddComponent<Collider>(Option, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(Option, C_TagComponent);
		//p_ecs.AddComponent<Logic>(Option, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(Option).SetPos({ 0.0f,-0.5f });
		//p_ecs.GetComponent<Transform>(Option).SetScale(1.0f, 0.2f);
		//p_ecs.GetComponent<Sprite>(Option).SetTexture("OptionsIdle");
		//p_ecs.GetComponent<Tag>(Option).SetTag("Options");
		//p_ecs.GetComponent<Collider>(Option)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(Option)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(Option).InsertScript(new ButtonResponse(), Option);

		//Entity HowToPlay = p_ecs.CreateEntity();
		//name.SetNameTag("HowToPlay");
		//p_ecs.AddComponent<NameTag>(HowToPlay, name);
		//p_ecs.AddComponent<Transform>(HowToPlay, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(HowToPlay, C_SpriteComponent);
		////p_ecs.AddComponent<RigidBody>(HowToPlay, rb);
		//p_ecs.AddComponent<Collider>(HowToPlay, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(HowToPlay, C_TagComponent);
		//p_ecs.AddComponent<Logic>(HowToPlay, C_LogicComponent);
		//p_ecs.GetComponent<Transform>(HowToPlay).SetPos({ 0.0f,-0.75f });
		//p_ecs.GetComponent<Transform>(HowToPlay).SetScale(1.0f, 0.2f);
		//p_ecs.GetComponent<Sprite>(HowToPlay).SetTexture("SmallButton");
		//p_ecs.GetComponent<Tag>(HowToPlay).SetTag("HowToPlay");
		//p_ecs.GetComponent<Collider>(HowToPlay)[0].mMax = { 0.5,0.5 };
		//p_ecs.GetComponent<Collider>(HowToPlay)[0].mMin = { -0.5,-0.5 };
		//p_ecs.GetComponent<Logic>(HowToPlay).InsertScript(new ButtonResponse(), Option);

		//Entity Background = p_ecs.CreateEntity();
		//name.SetNameTag("Background");
		//p_ecs.AddComponent<Transform>(Background, C_TransformComponent);
		//p_ecs.AddComponent<Sprite>(Background, sprite);
		//p_ecs.AddComponent<NameTag>(Background, name);
		//Entity hud = p_ecs.CreateEntity();
		//p_ecs.AddComponent<Transform>(hud, C_TransformComponent);
		//p_ecs.GetComponent<Transform>(hud).SetScale(3.0f, 1.0f);
		//p_ecs.AddComponent<HUDComponent>(hud, C_HUDComponent);
		//p_ecs.GetComponent<HUDComponent>(hud).SetOffset(vec2D(-3.0f, 3.0f));
		//p_ecs.GetComponent<HUDComponent>(hud).SetType(HUDComponent::ElementType::Static);
		//p_ecs.AddComponent<Tag>(hud, C_TagComponent);
		//p_ecs.AddComponent<Sprite>(hud, sprite);
		//p_ecs.GetComponent<Sprite>(hud).SetTexture("Blank");
		//p_ecs.AddComponent<Attributes>(hud, C_AttributesComponent);
		//p_ecs.AddComponent<NameTag>(hud, C_NameTagComponent);
		//p_ecs.GetComponent<NameTag>(hud).SetNameTag("HUD");
		//p_ecs.AddComponent<Logic>(hud, logic);
		//p_ecs.GetComponent<Logic>(hud).InsertScript(new HUDController(), hud);
		//Entity hpbar = p_ecs.CreateEntity();
		//p_ecs.AddComponent<Transform>(hpbar, C_TransformComponent);
		//p_ecs.GetComponent<Transform>(hpbar).SetScale(1.0f, 1.0f);
		//p_ecs.AddComponent<HUDComponent>(hpbar, C_HUDComponent);
		//p_ecs.GetComponent<HUDComponent>(hpbar).SetOffset(vec2D(-1.0f, 3.0f));
		//p_ecs.GetComponent<HUDComponent>(hpbar).SetType(HUDComponent::ElementType::HealthBar);
		//p_ecs.AddComponent<Tag>(hpbar, C_TagComponent);
		//p_ecs.AddComponent<Sprite>(hpbar, sprite);
		//p_ecs.GetComponent<Sprite>(hpbar).SetTexture("HPBar");
		//p_ecs.AddComponent<Attributes>(hpbar, C_AttributesComponent);
		//p_ecs.GetComponent<Attributes>(hpbar).SetHealth(100);
		//p_ecs.AddComponent<NameTag>(hpbar, C_NameTagComponent);
		//p_ecs.GetComponent<NameTag>(hpbar).SetNameTag("HPBar");
		//p_ecs.AddComponent<Logic>(hpbar, logic);
		//p_ecs.GetComponent<Logic>(hpbar).InsertScript(new HUDController(), hpbar);

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
		//p_ecs.GetComponent<Logic>(player).InsertScript(new PlayerControl(), player);
		//p_ecs.GetComponent<Logic>(player).InsertScript(new CollisionResponse(), player);
		/*p_ecs.AddComponent<Attributes>(player, C_AttributesComponent);*/
		//Entity enemy = p_ecs.CreateEntity();
		//Logic logic2;
		//p_ecs.AddComponent<Transform>(enemy, C_TransformComponent);
		//p_ecs.AddComponent<RigidBody>(enemy, rb);
		//p_ecs.AddComponent<Sprite>(enemy, sprite);
		//p_ecs.AddComponent<Collider>(enemy, C_ColliderComponent);
		//p_ecs.AddComponent<Tag>(enemy, C_TagComponent);
		//p_ecs.AddComponent<NameTag>(enemy, C_NameTagComponent);
		//p_ecs.GetComponent<NameTag>(enemy).SetNameTag("Enemy");
		//p_ecs.AddComponent<Logic>(enemy, logic2);
		//p_ecs.GetComponent<Logic>(enemy).InsertScript(new EnemyMovement(), enemy);
		//p_ecs.GetComponent<Logic>(enemy).InsertScript(new CollisionResponse(), enemy);
		//p_ecs.AddComponent<Attributes>(enemy, C_AttributesComponent);
		//p_ecs.GetComponent<Attributes>(enemy).SetDamage(10);
		
		//p_Audio->PlaySound("Assets/metadigger/HeroFightBossMusic.wav");
		p_Editor->is_ShowWindow = false;
		Graphic::camera.SetZoomLevel(0.25);
		p_Scene->DeserializeFromFile("Assets/Scene/LevelTest.json");

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
				mCollision->Update(Timer::GetInstance().GetGlobalDT());
				mPosUpdate->Update();
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<Tag>(i))
					{
						if (p_ecs.GetComponent<Tag>(i).GetTag() == "Enemy")
						{
							if (p_ecs.GetComponent<Attributes>(i).GetHealth() <= 0 && dynamic_cast<EnemyMovement*>(p_ecs.GetComponent<Logic>(i).GetScriptByName("EnemyMovement"))->GetState() == EnemyMovement::EnemyState::Death)
							{
								p_ecs.GetComponent<Sprite>(i).SetTexture("MeleeDeath");
								p_ecs.GetComponent<Collider>(i)[0].is_Alive = false;
								p_ecs.GetComponent<Collider>(i)[1].is_Alive = false;
								p_ecs.GetComponent<Sprite>(i).SetTexture("Blank");
							}
						}
					}
				}
			}
			end_state = p_GUI->Update(m_window);

			// test menu script

			p_Input->ResetPressedKey();//to fix the buggy error from glfwpollevent

			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			p_Scene->checkForSceneToLoad();

			FramePerSec::GetInstance().EndFrameCount();
			Timer::GetInstance().Update(Systems::API);
			std::cout << "End Frame" << std::endl;
		}
		mLogic->End();
		End();
	}

/*!*************************************************************************
End loop for application
****************************************************************************/
	void Application::End()
	{
		//p_Scene->SerializeToFile("Assets/Scene/Leveltest.json");
		p_Editor->End();
		p_Audio->Release();
	}
}
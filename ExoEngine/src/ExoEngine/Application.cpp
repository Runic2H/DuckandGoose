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
#include "ExoEngine/Scripts/HUDController.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "ExoEngine/Scripts/ButtonResponse.h"
#include "ExoEngine/Scripts/ScenerioScript.h"
#include "ExoEngine/Scripts/SliderScript.h"
#include "ExoEngine/Scripts/AudioManager.h"
#include "Platform/Logic/LogicSystem.h"
#include "ExoEngine/Scripts/PauseMenu.h"
#include "ExoEngine/GUI/GUI.h"
#include "ExoEngine/Scripts/DialogueManager.h"
#include <stdlib.h>

namespace EM {
	bool end_state{ false }; //placeholder

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
#if !DEBUG
		p_Scene->setSceneToLoad("Assets/Scene/SplashScreen.json");
#endif
		
		while (!glfwWindowShouldClose(m_window->GetWindow()) && end_state == false) //game loop
		{
			FramePerSec::GetInstance().StartFrameCount();
			Timer::GetInstance().Start(Systems::API);
			Timer::GetInstance().GetDT(Systems::API);

			p_Editor->Update();

			if (p_Editor->is_ShowWindow)
			{
				//p_Editor->Update();
				p_Editor->Draw();
			}
			
			p_Scene->checkForSceneToLoad();

			if (p_Scene->isGameplay == true)
				glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (!m_window->isWindowNotFocus)
			{
//#if !DEBUG
				mLogic->Update(Timer::GetInstance().GetGlobalDT());
//#endif
			}
			mCollision->Update(Timer::GetInstance().GetGlobalDT());
			mPosUpdate->Update();

			
			p_Audio->Update();
			
			if (p_Input->KeyPressed(GLFW_KEY_F3))
			{
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<EnemyAttributes>(i))
					{
						if (p_ecs.GetComponent<EnemyAttributes>(i).mEnemyType == EnemyAttributes::EnemyTypes::ENEMY_MELEE
							|| p_ecs.GetComponent<EnemyAttributes>(i).mEnemyType == EnemyAttributes::EnemyTypes::ENEMY_RANGED)
						{
							if (p_ecs.GetComponent<Transform>(i).GetPos().x < 5.67f)
							{
								p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive = true;
								p_ecs.GetComponent<EnemyAttributes>(i).mHealth = 0;
								p_ecs.GetComponent<EnemyAttributes>(i).mIsDamaged = true;
							}
						}
					}
				
					if (p_ecs.HaveComponent<Logic>(i) && p_ecs.GetComponent<Logic>(i).GetScriptByName("DialogueManager") != nullptr)
					{
						p_ecs.GetComponent<Logic>(i).GetScriptByName("DialogueManager")->mScriptPause = true;
					}
					//temper
					if (p_ecs.HaveComponent<PlayerAttributes>(i))
						p_ecs.GetComponent<Transform>(i).SetPos(5.67f, 0.0f);

				}
			}
			for (Entity entity = 0; entity < p_ecs.GetTotalEntities(); entity++)
			{
				if (p_ecs.HaveComponent<NameTag>(entity) && p_ecs.GetComponent<NameTag>(entity).GetNameTag() == "Splash Screen")
				{
					if (p_ecs.GetComponent<Transform>(entity).GetScale().x > 3.5f)
						p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
				}
			}
			end_state = p_GUI->Update(m_window);

			// test menu script

			p_Input->ResetPressedKey();//to fix the buggy error from glfwpollevent
			p_Input->ResetPressedMouse();


			m_window->Update(Timer::GetInstance().GetGlobalDT());
			mGraphics->Update(Timer::GetInstance().GetGlobalDT());
			
#if !DEBUG
			p_Editor->is_ShowWindow = false;
#endif 
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
		p_Editor->End();
		p_Audio->Release();
	}
}
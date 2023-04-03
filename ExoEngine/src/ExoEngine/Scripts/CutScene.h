/*!*************************************************************************
****
\file CutScene.h
\author Huang Xin Xiang
\par DP email: h.xinxiang@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/3/2023
\brief	Script for Dialogue Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "Platform/Graphics/Camera2D.h"
#include "Platform/Graphics/Graphics.h"
#include "ExoEngine/ECS/SceneManager.h"
#include "ExoEngine/Input/Input.h"

namespace EM
{
	/*!*************************************************************************
	Class for Cutscenes Script
	****************************************************************************/
	class CutScene : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Cutscenes
		****************************************************************************/
		CutScene() : timer(0), mScenePicker{ 0 }, mSwitchAudio{ 1 } {}
		/*!*************************************************************************
		Default destructor for Cutscenes
		****************************************************************************/
		~CutScene() = default;
		/*!*************************************************************************
		Returns a new copy of Cutscenes Script
		****************************************************************************/
		virtual CutScene* Clone() const override
		{
			return new CutScene(*this);
		}
		/*!*************************************************************************
		Start State of Cutscenes Script
		****************************************************************************/
		virtual void Start() override
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.GetComponent<NameTag>(i).GetNameTag() == "CutScene Controller")
				{
					EM::Graphic::mcamera->SetPosition({ 0.0f, 0.0f, 0.0f });
				}
			}
			if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > mSwitchAudio))
			{
				p_ecs.GetComponent<Audio>(GetScriptEntityID())[mSwitchAudio].should_play = true;
			}
		}
		/*!*************************************************************************
		Update Loop of Cutscenes Script
		****************************************************************************/
		virtual void Update(float Frametime) override
		{
			timer += Frametime;
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				++mScenePicker;
				if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > mSwitchAudio))
				{
					p_ecs.GetComponent<Audio>(GetScriptEntityID())[mSwitchAudio].should_stop = true;
				}
				++mSwitchAudio;
				EM::Graphic::mcamera->SetPosition({ p_ecs.GetComponent<Transform>(mScenePicker).GetPos().x
					, p_ecs.GetComponent<Transform>(mScenePicker).GetPos().y, 0.0f });
				p_Input->mMouseStatus[GLFW_MOUSE_BUTTON_LEFT] = GLFW_RELEASE;
				timer = 0.0f;
				if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > 10))
				{
					p_ecs.GetComponent<Audio>(GetScriptEntityID())[10].should_play = true;
				}

				if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > mSwitchAudio))
				{
					p_ecs.GetComponent<Audio>(GetScriptEntityID())[mSwitchAudio].should_play = true;
				}

			}
			if (timer >= 5.0f)
			{
				++mScenePicker;
				++mSwitchAudio;
				EM::Graphic::mcamera->SetPosition({ p_ecs.GetComponent<Transform>(mScenePicker).GetPos().x
					, p_ecs.GetComponent<Transform>(mScenePicker).GetPos().y, 0.0f });
				timer = 0.0f;
				if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > mSwitchAudio))
				{
					p_ecs.GetComponent<Audio>(GetScriptEntityID())[mSwitchAudio].should_play = true; //cutscene audio
				}
			}

			if (mScenePicker == 9)
			{
				//transit to another scene
				p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
			}



		}
		/*!*************************************************************************
		End State for Cutscenes
		****************************************************************************/
		virtual void End() override
		{
			delete this;
		}
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override
		{
			return "CutScene";
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		float timer;
		Entity mScenePicker;
		int mSwitchAudio;
	};
}
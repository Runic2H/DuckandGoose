/*!*************************************************************************
****
\file DialogueManager.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Dialogue Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/Graphics/Camera2D.h"

namespace EM
{
	/*!*************************************************************************
	Class for Dialogue Manager Script
	****************************************************************************/
	class DialogueManager : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Dialogue Manager
		****************************************************************************/
		DialogueManager() : mDialogues{"HowToPlay", "Dialogue1", "Dialogue2", "Dialogue3", "Dialogue4", "Dialogue5" }, counter{ 0 }, MaxCounter{ 3 } {}
		/*!*************************************************************************
		Default destructor for Dialogue Manager
		****************************************************************************/
		~DialogueManager() = default;
		/*!*************************************************************************
		Returns a new copy of Dialogue Manager Script
		****************************************************************************/
		virtual DialogueManager* Clone() const override
		{
			return new DialogueManager(*this);
		}
		/*!*************************************************************************
		Start State of DialogueManager Script
		****************************************************************************/
		virtual void Start() override
		{
		}
		/*!*************************************************************************
		Update Loop of DialogueManager Script
		****************************************************************************/
		virtual void Update(float Frametime) override
		{

			UNREFERENCED_PARAMETER(Frametime);
			Entity i{0};
		
			for (Entity e = 0; e < p_ecs.GetTotalEntities(); ++e)
			{
				if (p_ecs.HaveComponent<PlayerAttributes>(e))
				{
					if (p_ecs.GetComponent<Transform>(e).GetPos().x >= p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos().x)
					{
						p_ecs.GetComponent<Sprite>(e).SetTexture("Idle");
						p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetLayerOrder(5);
						if (counter > 0)
						{
							p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetPos(p_ecs.GetComponent<Transform>(e).GetPos().x, p_ecs.GetComponent<Transform>(e).GetPos().y - 0.140f);
							p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(0.7f, 0.125f);
						}
						else 
						{
							p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetPos(p_ecs.GetComponent<Transform>(e).GetPos().x, p_ecs.GetComponent<Transform>(e).GetPos().y);
							p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(0.7f, 0.4f);
						}
						
						if (p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetTexture() == "Dialogue3") { MaxCounter = 4; counter = 3; }
						else if (p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetTexture() == "Dialogue4") { MaxCounter = 5; counter = 4; }
						else if (p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetTexture() == "Dialogue5") { MaxCounter = 6; counter = 5; }
						if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
						{
							++counter;
							if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > 0))
							{
								p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].should_play = true;
							}
							p_Input->mMouseStatus[GLFW_MOUSE_BUTTON_LEFT] = GLFW_RELEASE;
						}
						if (counter < MaxCounter)
						{
							p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture(mDialogues[counter].c_str());
							for (i = 0; i < p_ecs.GetTotalEntities(); ++i)
							{
								if (p_ecs.HaveComponent<Logic>(i) && p_ecs.HaveComponent<PlayerAttributes>(i))
								{
									p_ecs.GetComponent<Logic>(i).GetScriptByName("PlayerControl")->mScriptPause = true;
								}
							}
						}
						else
						{
							for (i = 0; i < p_ecs.GetTotalEntities(); ++i)
							{
								if (p_ecs.HaveComponent<Logic>(i) && p_ecs.HaveComponent<PlayerAttributes>(i))
								{
									p_ecs.GetComponent<Logic>(i).GetScriptByName("PlayerControl")->mScriptPause = false;
								}
							}
							this->mScriptPause = true;
							p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blank");
						}
					}
				}
			}
				
			
		}
		/*!*************************************************************************
		End State for DialogueManager
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
			return "DialogueManager";
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		std::string mDialogues[6];
		int counter;
		int MaxCounter;
	};
}
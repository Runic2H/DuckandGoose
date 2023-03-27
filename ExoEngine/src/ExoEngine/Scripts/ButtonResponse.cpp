/*!*************************************************************************
****
\file ButtonResponse.cpp
\author Lau Yong Hui
\par DP email:l.yonghui.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM250
\date 20/01/2023
\brief	Script That allow buttons to work when selected and clicked on

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/

#include "empch.h"
#include "ButtonResponse.h"
#include "../ECS/SceneManager.h"
#include "ExoEngine/GUI/GUI.h"
#include "Platform/Graphics/Graphics.h"


namespace EM
{

	void ButtonResponse::Start() {}
	
	void ButtonResponse::Update(float Frametime)
	{
		
		Graphic::camera.SetPosition({ 0.0f,0.0f,0.0f });
		UNREFERENCED_PARAMETER(Frametime);
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& ID_tag = p_ecs.GetComponent<Tag>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		auto& spt = p_ecs.GetComponent<Sprite>(GetScriptEntityID());
		


		if (spt.GetTexture() == "HowToPlay" && p_Input->KeyPressed(GLFW_KEY_ESCAPE))
		{
			spt.SetTexture("htp_button_Idle");
			transform.SetPos({ 0.0f,-0.25f });
			transform.SetScale(1.0f, 0.2f);
			p_GUI->toggle_HTP();
		}

		if ( p_GUI->Check_HTP() == false)
		{ 
			
			if (curr_state != button_state::click)
				curr_state = button_state::idle;

		
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::idle)
			{
				curr_state = button_state::click;
			}

			else if (p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_LEFT) && curr_state == button_state::click)
			{
				curr_state = button_state::release;
			}
		}
		

		if (is_within_box(p_GUI->MousePosition, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
		{
			if (initial_hover && p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > 0) && (p_GUI->Check_HTP() == false))
			{
				p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].should_play = true; //menu hover audio
				initial_hover = false;
			}

			if (ID_tag.GetTag() == "Start" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Start_Hover");
			}

			if (ID_tag.GetTag() == "Quit" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Quit_Hover");
			}

			if (ID_tag.GetTag() == "Options" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Options_Hover");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("htp_button_Hover");
			}

			if (ID_tag.GetTag() == "MainMenu" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("MM_B");
			}

			if (ID_tag.GetTag() == "Restart" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("RESTART_B");
			}

			if (ID_tag.GetTag() == "Resume" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Resume_Hover");
			}

			if (ID_tag.GetTag() == "PRestart" && !(p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)))
			{
				spt.SetTexture("Restart_Hover");
			}

			if (ID_tag.GetTag() == "Back")
			{
				spt.SetTexture("BACK_B");//to be change
			}
			
			if (curr_state == button_state::release)
			{

				if (ID_tag.GetTag() == "Start" && p_GUI->Check_HTP() == false)
				{
				
					Graphic::mcamera->SetZoomLevel(0.25f);
					p_Scene->setSceneToLoad("Assets/Scene/CutScene.json");
				}

				if (ID_tag.GetTag() == "Restart" )
				{
					p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
				}

				if (ID_tag.GetTag() == "Quit" && p_GUI->Check_HTP() == false)
				{
					p_GUI->toggle_script();
				}

				if (ID_tag.GetTag() == "HowToPlay" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("HowToPlay");
					transform.SetScale({ 4.170206546783447f,1.9999960660934448f });
					transform.SetPos({ 0.0f,0.0f });
					p_GUI->toggle_HTP();
				}

				if (ID_tag.GetTag() == "Options" && p_GUI->Check_HTP() == false)
				{
					p_Scene->setSceneToLoad("Assets/Scene/Option.json");
				}

				if (ID_tag.GetTag() == "MainMenu" && p_GUI->Check_HTP() == false)
				{
					//p_GUI->toggle_menu();
					p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
				}
				if (ID_tag.GetTag() == "PResart")
				{
					Graphic::mcamera->SetZoomLevel(0.25f);
					p_Scene->setSceneToLoad("Assets/Scene/Elton.json");
				}

				if (ID_tag.GetTag() == "Mute")
				{
					p_Audio->SetVolumeByChannel(p_Audio->GetMasterChannelGroup(), 0.0f);
				}

				if (ID_tag.GetTag() == "Back")
				{
					p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
				}


			
			}

			if (curr_state == button_state::click)
			{
				if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && ((p_ecs.GetComponent<Audio>(GetScriptEntityID())).GetSize() > 1) && (p_GUI->Check_HTP() == false))
				{
					p_ecs.GetComponent<Audio>(GetScriptEntityID())[1].should_play = true; //menu click audio
				}

				if (ID_tag.GetTag() == "Start" && p_GUI->Check_HTP() == false)
				{
				//	p_GUI->toggle_menu();
					spt.SetTexture("Start_Click");
				}

				if (ID_tag.GetTag() == "Quit" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("Quit_Click");
				}

				if (ID_tag.GetTag() == "MainMenu" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("MM_R");

				}

				if (ID_tag.GetTag() == "Restart" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("RESTART_R");

				}

				if (ID_tag.GetTag() == "HowToPlay")
				{
					spt.SetTexture("htp_button_Click");
				}

				if (ID_tag.GetTag() == "Options" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("Options_Click");
				}

				if (ID_tag.GetTag() == "Resume")
				{
					spt.SetTexture("Resume_Click");
					
				}
				if (ID_tag.GetTag() == "PRestart")
				{
					spt.SetTexture("Restart_Click");//to be change
				}

				if (ID_tag.GetTag() == "Mute")
				{
					spt.SetTexture("Mute_Click");//to be change
				}

				if (ID_tag.GetTag() == "Back")
				{
					spt.SetTexture("BACK_R");//to be change
				}
				
			}

			
		}
		else
		{
			initial_hover = true;

			if (ID_tag.GetTag() == "Start")
			{
				spt.SetTexture("Start_Idle");
			}

			if (ID_tag.GetTag() == "Quit")
			{
				spt.SetTexture("Quit_Idle");
			}
			if (ID_tag.GetTag() == "Options")
			{
				spt.SetTexture("Options_Idle");
			}

			if (ID_tag.GetTag() == "MainMenu")
			{
				spt.SetTexture("MM_Y");
			}

			if (ID_tag.GetTag() == "Restart")
			{
				spt.SetTexture("RESTART_Y");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay")
			{
				spt.SetTexture("htp_button_Idle");
			}

			if (ID_tag.GetTag() == "Resume")
						{
							spt.SetTexture("Resume_Idle");
						}
			if (ID_tag.GetTag() == "PRestart")
						{
							spt.SetTexture("Restart_Idle");//to be change
						}
			if (ID_tag.GetTag() == "Back")
			{
				spt.SetTexture("BACK_Y");//to be change
			}
		}

	}

	void ButtonResponse::End()
	{
		delete this;
	}

	ButtonResponse* ButtonResponse::Clone() const
	{
		return new ButtonResponse(*this);
	}

	
	std::string ButtonResponse::GetScriptName()
	{
		return "ButtonResponse";
	}

	bool ButtonResponse::is_within_box(glm::vec2 cur, Collider box, Transform trans)
	{
		if (cur.x  > ((box[0].mMin.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y > (box[0].mMin.y * (trans.GetScale().y / 2) + trans.GetPos().y) &&
			cur.x  < ((box[0].mMax.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y < (box[0].mMax.y * (trans.GetScale().y / 2) + trans.GetPos().y))
		{
		return true;//return true if the position of the cursor is between both of the button minimun and maximum bounding point
		}
		else
		return false;// return false if it isnt
	}
}
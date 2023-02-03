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


namespace EM
{

	void ButtonResponse::Start()
	{	clicked = false;
		selected= false;
	}

	/*transform.GetPos().x + collider.GetOffset().x , transform.GetPos().y + collider.GetOffset().y, 0.0f },
						{ collider.GetMin().x - collider.GetMax().x , collider.GetMin().y - collider.GetMax().y },
						{ 1.0f, 0.0f, 0.0f,1.0f });*/
	
	void ButtonResponse::Update(float Frametime)
	{
		
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		auto& ID_tag = p_ecs.GetComponent<Tag>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		auto& spt = p_ecs.GetComponent<Sprite>(GetScriptEntityID());
		
		if (spt.GetTexture() == "HowToPlay" && p_Input->KeyPressed(GLFW_KEY_ESCAPE))
		{

			spt.SetTexture("HTPButtonIdle");
			transform.SetPos({ 0.0f,-0.75f });
			transform.SetScale(0.9f, 0.2f);
		}

		if (is_within_box(p_GUI->MousePosition, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
		{
			if (ID_tag.GetTag() == "Start")
			{
				spt.SetTexture("StartHover");
			}

			if (ID_tag.GetTag() == "Quit")
			{
				spt.SetTexture("QuitHover");
			}

			if (ID_tag.GetTag() == "Options")
			{
				spt.SetTexture("OptionsHover");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay")
			{
				spt.SetTexture("HTPButtonHover");
				std::cout << "hello";
			}
			selected = true;
			std::cout << tag.GetNameTag();
			std::cout << "minX: " << (col[0].mMin.x + transform.GetPos().x)<< "minY: " << (col[0].mMin.y + transform.GetPos().y) << "MaxX: " << (col[0].mMax.x + transform.GetPos().x) << "MaxY: " << (col[0].mMax.y + transform.GetPos().y) << std::endl;
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				if (ID_tag.GetTag() == "Start" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("StartClick");
					p_GUI->toggle_menu();
					p_Scene->setSceneToLoad("Assets/Scene/Level.json");
				}

				if (ID_tag.GetTag() == "Quit" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("QuitClick");
					p_GUI->toggle_script();
				}

				if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() == "HTPButtonHover")
				{
					//spt.SetTexture("HTPButtonClick");
					spt.SetTexture("HowToPlay");
					transform.SetScale({ 4.170206546783447f,1.9999960660934448f });
					transform.SetPos({ 0.0f,0.0f });
					p_GUI->toggle_HTP();
				}

				if (ID_tag.GetTag() == "Options" && p_GUI->Check_HTP() == false)
				{
					spt.SetTexture("OptionsClick");
				}
			}

			else
			{
				clicked = false;
			}
		}
		else
		{
			if (ID_tag.GetTag() == "Start")
			{
				spt.SetTexture("StartIdle");
			}

			if (ID_tag.GetTag() == "Quit")
			{
				spt.SetTexture("QuitIdle");
			}
			if (ID_tag.GetTag() == "Options")
			{
				spt.SetTexture("OptionsIdle");
			}

			if (ID_tag.GetTag() == "HowToPlay" && spt.GetTexture() != "HowToPlay")
			{
				spt.SetTexture("HTPButtonIdle");
				p_GUI->toggle_HTP();
			}
			selected = false;

			
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
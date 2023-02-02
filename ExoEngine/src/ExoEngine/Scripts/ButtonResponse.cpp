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
		
		
		if (is_within_box(p_GUI->MousePosition, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
		{
			selected = true;
			std::cout << tag.GetNameTag();
			std::cout << "minX: " << (col[0].mMin.x + transform.GetPos().x)<< "minY: " << (col[0].mMin.y + transform.GetPos().y) << "MaxX: " << (col[0].mMax.x + transform.GetPos().x) << "MaxY: " << (col[0].mMax.y + transform.GetPos().y) << std::endl;
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				if (ID_tag.GetTag() == "Start")
				{
					p_Scene->setSceneToLoad("Assets/Scene/Level.json");
				}

				if (ID_tag.GetTag() == "Quit")
				{
					p_GUI->toggle_script();
				}

				if (ID_tag.GetTag() == "HowToPlay")
				{
					spt.SetTexture("HowToPlay");
					transform.SetScale({ 4.170206546783447f,1.9999960660934448f });
					transform.SetPos({ 0.0f,0.0f });
				}
			}

			else
			{
				clicked = false;
			}
		}
		else
			selected = false;

		if (spt.GetTexture() == "HowToPlay" && p_Input->KeyPressed(GLFW_KEY_SPACE))
		{
			spt.SetTexture("SmallButton");
			transform.SetPos({ 0.0f,-0.75f });
			transform.SetScale(0.6f, 0.2f);
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
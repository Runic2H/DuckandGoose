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
		//auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
		//auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		//auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		//auto& btn = p_ecs.GetComponent<Button>(GetScriptEntityID());
		//std::cout << transform.GetPos().x + col.GetOffset().x<<std::endl;
		//vec2D tempos = transform.GetPos() + col.GetOffset();
	//	vec2D tempscale = col.GetMin() - col.GetMax();

	//	std::cout << "X:" << tempos.x - tempscale.x*0.5f;
		//position.x - size.x * 0.5f
		
		
		
		
		//if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
		//{
		//	btn.Toggleclicked();
		//	std::cout << btn.CheckIfclicked();
		//}
		
		if (is_within_box(p_GUI->MousePosition, col, transform))//if system is pause and continue button is pressed, tell the system to resume the game
		{
			selected = true;
			std::cout << "X:" << p_GUI->MousePosition.x << " Y:" << p_GUI->MousePosition.y << " ";
			std::cout << "minX: " << (col[0].mMin.x + transform.GetPos().x)<< "minY: " << (col[0].mMin.y + transform.GetPos().y) << "MaxX: " << (col[0].mMax.x + transform.GetPos().x) << "MaxY: " << (col[0].mMax.y + transform.GetPos().y) << std::endl;
			if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				p_Scene->setSceneToLoad("Assets/Scene/Level.json");
				
			}
			else
			{
				clicked = false;
				std::cout << "X:" << p_GUI->MousePosition.x << " Y:" << p_GUI->MousePosition.y << " " << std::endl;
			}
		}
		else
			std::cout << "X:" << p_GUI->MousePosition.x << " Y:" << p_GUI->MousePosition.y << " "<< std::endl;
			selected = false;
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
		//We factor in aspect ratio since graphic scale is proportionate to aspect ratio instead of screen
		//std::cout << (p_GUI->MousePosition.x * p_GUI->Get_AspectRatio())<< "  " << box.GetMin().x<<std::endl;
		if (cur.x  > ((box[0].mMin.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y > (box[0].mMin.y * (trans.GetScale().y / 2) + trans.GetPos().y) &&
			cur.x  < ((box[0].mMax.x * (trans.GetScale().x/2)) + trans.GetPos().x) && cur.y < (box[0].mMax.y * (trans.GetScale().y / 2) + trans.GetPos().y))
		{
		return true;//return true if the position of the cursor is between both of the button minimun and maximum bounding point
		}
		else
		return false;// return false if it isnt
	}
}
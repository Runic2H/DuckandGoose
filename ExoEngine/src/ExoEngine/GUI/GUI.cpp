#include"Platform/Window/Window.h"
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/Application.h"
#include "GUI.h"
namespace EM
{
	std::unique_ptr<gui_system> m_Instance;

	 std::unique_ptr<gui_system>& gui_system::GetInstance()
	{
		if (!m_Instance)
		{
			m_Instance = std::make_unique<gui_system>();
		}
		return m_Instance;
	}
	 bool gui_system::is_within_box(glm::vec2 cur, button_bb box)
	 {
		 //We factor in aspect ration since graphic scale is proportionate to aspect ration instead of screen
		 if ((cur.x * AR > box.min.x && cur.y > box.min.y) && (cur.x * AR < box.max.x && cur.y < box.max.y))
			 return true;
		 else
			 return false;
	 }
	 void gui_system::set_pause_button(vec2D pos, float scaleX, float scaleY)
	 {
		 pause_button.max.y = pos.y + scaleY / 2;
		 pause_button.max.x = (pos.x + (scaleX / 2));
		 pause_button.min.y = pos.y - scaleY / 2;
		 pause_button.min.x = (pos.x - (scaleX / 2));


		
	 }

	 void gui_system::set_continue_button(vec2D pos, float scaleX, float scaleY)
	 {
		 continue_button.max.y = pos.y + scaleY / 2;
		 continue_button.max.x = (pos.x + (scaleX / 2));
		 continue_button.min.y = pos.y - scaleY / 2;
		 continue_button.min.x = (pos.x - (scaleX / 2));
	 }

	bool  gui_system::Update(Window* screen)
	{
		float mouse_posX = static_cast<float>(screen->Getter().mouseX);
		float mouse_posY = static_cast<float>(screen->Getter().mouseY);
		float screen_width = static_cast<float>(screen->Getter().m_Width);
		float screen_height = static_cast<float>(screen->Getter().m_Height);
		glm::vec2 mouse_pos{ static_cast<float>(screen->Getter().mouseX) , static_cast<float>(screen->Getter().mouseY) };
		glm::vec2 screen_size{ static_cast<float>(screen->Getter().m_Width),static_cast<float>(screen->Getter().m_Height) };
		AR = screen_width / screen_height;
		
		mouse_pos.x /= screen_size.x; 
		mouse_pos.y /= screen_size.y;	
		mouse_pos *= 2.0f;
		mouse_pos -= glm::vec2{ 1, 1 };
		mouse_pos.y *= -1;
		glm::vec4 temp{  mouse_pos,0,0 };

		if (is_pause == true)
		{	
			if (is_within_box(mouse_pos, pause_button) && p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				return true;
			}

			if (is_within_box(mouse_pos, continue_button) && p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				is_pause = false;
			}
			else return false;
				
		}
		return false;
	}

	

	bool gui_system::check_pause()//getter function for pause state
	{
		return is_pause;
	}

	void gui_system::toggle_pause()//if game is pause,unpause it. Or pause it if it is unpause.
	{
		if (is_pause == false)
		{
			is_pause = true;
		}
		else
			is_pause = false;
	}

	

}

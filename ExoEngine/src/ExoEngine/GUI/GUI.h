#pragma once
#include "empch.h"
#include"ExoEngine/Input/Input.h"
#include"ExoEngine/Math/Math.h"
//#include "ExoEngine/ECS/Components.h"
#include "../../Platform/System/System.h"
#include"Platform/Window/Window.h"
#include "ExoEngine/Core.h"
#include <vector>

#define p_GUI EM::gui_system::GetInstance()

namespace EM
{
	

	//bool check_cur_pos();


	class EM_API gui_system 
	{
	private:
		bool is_pause = { false }; //check if pause

		struct button_bb
		{
			glm::vec2 max{ 0,0 };
			glm::vec2 min{ 0,0 };
		};

		button_bb pause_button;
		button_bb continue_button;
		float AR;

	public:
		static std::unique_ptr<gui_system>& GetInstance();
		//void Init();
		bool Update(Window* screen);
		bool pause_switch = false;
		glm::mat4 VPmat;
	
		//void set_ButtonPos(Vec3 pos);
		//void End();
	//	void Draw_continue();
		

		void set_pause_button(vec2D pos, float scaleX, float scaleY);
		void set_continue_button(vec2D pos, float scaleX, float scaleY);
		void toggle_pause();
		bool check_pause();
		bool is_within_box(glm::vec2 cur, button_bb box);
		
		

		//vec2D update_curPos(Window screen);
	};



}

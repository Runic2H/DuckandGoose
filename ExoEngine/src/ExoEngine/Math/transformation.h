#pragma once

#include "empch.h"
#include "Vmath.h"


namespace EM 
{
	class Transform2
	{
	public:
		Transform2();
		Transform2(vec2D Pos, vec2D Scale, float Rotation);

		void set_pos(vec2D Pos);
		void set_scale(vec2D Scale);
		void set_rotation(float Rotation);
		void set_collision_flag(bool flag);

		vec2D get_pos();
		float get_rotation();
		bool  get_collision();

		void add_pos(vec2D Pos);
		void subtract_pos(vec2D Pos);
		void multiply_scale(vec2D Scale);
	
	private:
		vec2D pos;
		vec2D scale;
		float rotation;
		bool collision_flag{ false };
	};

}
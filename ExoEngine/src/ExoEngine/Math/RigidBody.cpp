#include "RigidBody.h"

namespace EM
{


	RigidBody2::RigidBody2( vec2D vel)
	{
		velocity = vel;
		
	}

	/*void RigidBody2::update_physics()
	{
		pos += velocity * pos;
	}*/

	void RigidBody2::set_aabb(aabb box)
	{
		bounding_box = box;
	}
	
	void RigidBody2::calculate_accel()
	{
		aceleration = force / mass;
	}
	//reset function
	void RigidBody2::reset_force()
	{
		force.value.x = 0;
		force.value.y = 0;
	}

	vec2D RigidBody2::get_accel()
	{
		return aceleration;
	}
	vec2D RigidBody2::get_vel()
	{
		return velocity;
	}
	vec2D RigidBody2::get_force()
	{
		return force;
	}

	void RigidBody2::reset_accel()
	{
		aceleration.vector.x = 0;
		aceleration.vector.y = 0;
	}
	void RigidBody2::reset_velocity()
	{
		velocity.vector.x = 0;
		velocity.vector.y = 0;
	}

	//helper function
	void RigidBody2::set_weight(float Mass)
	{
		mass = Mass;
	}

	void RigidBody2::set_velocity(vec2D Velocity)
	{
		velocity.vector.y = Velocity.vector.y;
		velocity.vector.x = Velocity.vector.x;
	}

	void RigidBody2::set_acceleration(vec2D Accel)
	{
		aceleration = Accel;
	}

	void RigidBody2::set_pos(vec2D Pos)
	{
		pos = Pos;
		bounding_circle.center = Pos;
	}
	void RigidBody2::set_Rad(float radius)
	{
		bounding_circle.radius = radius;
	}


	void RigidBody2::add_weight(float Mass)
	{
		mass += Mass;
	}
	void RigidBody2::add_Force(vec2D Force)
	{
		force += Force;
	}
	void RigidBody2::add_acceleration(vec2D Accel)
	{
		aceleration += Accel;
	}
}
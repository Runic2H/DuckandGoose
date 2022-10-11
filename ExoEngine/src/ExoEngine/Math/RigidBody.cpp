#include "RigidBody.h"

namespace EM
{


	RigidBody::RigidBody(vec2D point, vec2D vel, Col_Type type)
	{
		pos = point;
		velocity = vel;
		Type = type;
	}

	void RigidBody::update_physics()
	{
		pos += velocity*dt;
	}

	void RigidBody::set_aabb(aabb box)
	{
		bounding_box = box;
	}
	
	void RigidBody::calculate_accel()
	{

	}
	//reset function
	void RigidBody::reset_force()
	{
		force = 0;
	}

	vec2D RigidBody::get_accel()
	{
		return aceleration;
	}
	vec2D RigidBody::get_vel()
	{
		return velocity;
	}
	float RigidBody::get_force()
	{
		return force;
	}

	void RigidBody::reset_accel()
	{
		aceleration.vector.x = 0;
		aceleration.vector.y = 0;
	}
	void RigidBody::reset_velocity()
	{
		velocity.vector.x = 0;
		velocity.vector.y = 0;
	}

	//helper function
	void RigidBody::set_weight(float Mass)
	{
		mass = Mass;
	}

	void RigidBody::set_velocity(vec2D Velocity)
	{
		velocity = Velocity;
	}

	void RigidBody::set_acceleration(vec2D Accel)
	{
		aceleration = Accel;
	}

	void RigidBody::set_pos(vec2D Pos)
	{
		pos = Pos;
		bounding_circle.center = Pos;
	}
	void RigidBody::set_Rad(float radius)
	{
		bounding_circle.radius = radius;
	}


	void RigidBody::add_weight(float Mass)
	{
		mass += Mass;
	}
	void RigidBody::add_Force(float Velocity)
	{
		velocity += Velocity;
	}
	void RigidBody::add_acceleration(float Accel)
	{
		aceleration += Accel;
	}
}
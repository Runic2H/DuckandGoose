#include"physics_system.h"

#include"RigidBody.h"
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
namespace EM {
	extern ECS ecs;

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Update(float dt)
	{
		for (auto const& Entity : mEntities)
		{
			auto& rigidBody2 = ecs.GetComponent<RigidBody2>(Entity);
			auto& transformation = ecs.GetComponent<Transform>(Entity);

			vec2D currpos = transformation.GetPos();
			currpos += rigidBody2.velocity * dt;
			transformation.SetPos(currpos);
		}

		
	}
	


	void PhysicsSystem::calculate_accel(RigidBody2 obj)
	{
		obj.aceleration = obj.force / obj.mass;
	}
	//reset function
	void PhysicsSystem::reset_force(RigidBody2 obj)
	{--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		obj.force.x = 0;
		obj.force.y = 0;
	}

	void PhysicsSystem::reset_accel(RigidBody2 obj)
	{
		obj.aceleration.x = 0;
		obj.aceleration.y = 0;
	}
	void PhysicsSystem::reset_velocity(RigidBody2 obj)
	{
		obj.velocity.x = 0;
		obj.velocity.y = 0;
	}

	void PhysicsSystem::multiply_scale(Transform2 obj, vec2D Scale)
	{
		obj.scale += Scale.x;
		obj.scale.y += Scale.y;
	}
}
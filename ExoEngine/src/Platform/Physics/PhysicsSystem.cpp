#include "empch.h"
#include "PhysicsSystem.h"
#include "../ECS/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	extern ECS ecs;

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Update()
	{
		for (auto& Entity : mEntities)
		{
			auto mTrans = ecs.GetComponent<Transform>(Entity);
			auto mRigid = ecs.GetComponent<RigidBody>(Entity);
			mTrans.SetPos(mRigid.GetNextPos());
		}
	}

	void PhysicsSystem::End() {

	}

	/*void PhysicsSystem::calculate_accel(RigidBody2 obj)
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
	}*/
}
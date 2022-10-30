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
<<<<<<<< HEAD:ExoEngine/src/ExoEngine/Math/PhysicsSystem.cpp
        	auto mRigid = ecs.GetComponent<RigidBody>(Entity);
			mTrans.SetPos(mRigid.GetNextPos());
		}
	}
	
	void PhysicsSystem::End() {
		
	}

========
			auto mRigid = ecs.GetComponent<RigidBody>(Entity);
			mTrans.SetPos(mRigid.GetNextPos());
		}
	}

	void PhysicsSystem::End() {

	}

>>>>>>>> a2c28223adcbb8c8baa1c79e249d860e41369b43:ExoEngine/src/Platform/Physics/PhysicsSystem.cpp
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
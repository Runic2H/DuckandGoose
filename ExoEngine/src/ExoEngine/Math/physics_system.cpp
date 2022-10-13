#include"physics_system.h"

#include"RigidBody.h"
//#include "../ECS/ECS.h"
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
			currpos += rigidBody2.get_vel() * dt;
			transformation.SetPos(currpos);
		}

		
	}
}
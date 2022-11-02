#include "empch.h"
#include "PhysicsSystem.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	//extern ECS ecs;

	void PhysicsSystem::Init()
	{

	}

	void PhysicsSystem::Update()
	{
		Timer::GetInstance().Start(Systems::PHYSICS);
		Timer::GetInstance().GetDT(Systems::PHYSICS);
		for (auto& Entity : mEntities)
		{
			auto& mTrans = p_ecs.GetComponent<Transform>(Entity);
			auto& mRigid = p_ecs.GetComponent<RigidBody>(Entity);
			mTrans.SetPos(mRigid.GetNextPos());
		}
		Timer::GetInstance().Update(Systems::PHYSICS);
	}

	void PhysicsSystem::End() {

	}
}
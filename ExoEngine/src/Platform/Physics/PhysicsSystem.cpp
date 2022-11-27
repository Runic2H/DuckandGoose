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
		for (const auto& entity : mEntities)
		{
			auto& mTrans = p_ecs.GetComponent<Transform>(entity);
			auto& mRigid = p_ecs.GetComponent<RigidBody>(entity);

			if (entity == mTrans.GetComponentEntityID())
			{
				mTrans.SetPos(mRigid.GetNextPos());
			}
			else
			{
				mTrans.SetPos(p_ecs.GetComponent<RigidBody>(mTrans.GetComponentEntityID()).GetNextPos());
			}
		}
		Timer::GetInstance().Update(Systems::PHYSICS);
	}

	void PhysicsSystem::End() {

	}
}
/*!*************************************************************************
****
\file			enemy_movement.cpp
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			26-10-2022
\brief			This file contains the necessary function definitions enemy 
                movement

****************************************************************************
***/
#include "empch.h"
#include "player_movement.h"
#include "../ECS/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"

namespace EM {
    extern ECS ecs;
    extern Entity player;
    void Enemy_Movement::Init() {
    }
	void Enemy_Movement::Update(float dt) {
        auto pTrans = ecs.GetComponent<Transform>(player);
        auto pRigid = ecs.GetComponent<RigidBody>(player);
        entityPhysics phys;
        for (auto const& Entity : mEntities)
		{
			auto mTrans = ecs.GetComponent<Transform>(Entity);
        	auto mRigid = ecs.GetComponent<RigidBody>(Entity);

		}
    }
	void Enemy_Movement::End() {
    }
}
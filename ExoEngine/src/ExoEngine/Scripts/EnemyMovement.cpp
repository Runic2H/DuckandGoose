/*!*************************************************************************
****
\file EnemyMovement.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for basic pathfinding for Enemy Movement will be expanded
for more complex pathfinding

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyMovement.h"
#include "GateController.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for new Enemy Movement Scripts
	****************************************************************************/
	EnemyMovement::EnemyMovement() : mState{ EnemyState::Patrolling }, mAttackCooldown{ 0.0f }, mAttackTime{ 0.0f }, mOrigin{ vec2D() }, mPatrolling{ false }, mDest{ vec2D() }, mPatrolTimer{ 2.0f }, mPatrolTime{ 2.0f } {}

	/*!*************************************************************************
	returns an instance for a new Enemy Movement Script
	****************************************************************************/
	EnemyMovement* EnemyMovement::Clone() const
	{
		return new EnemyMovement(*this);
	}

	/*!*************************************************************************
	Init for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Start() {
		mOrigin = p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos();
	}

	/*!*************************************************************************
	Update loop for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Update(float Frametime)
	{
		//if patrolling state
		if (mState == EnemyState::Patrolling) {
			//check if moving
			if (!mPatrolling) {
				//std::cout << "At Destination" << std::endl;
				//if not moving, set destination
				mDest.x = mOrigin.x + ((rand() % 100) - 50) / 50;
				mDest.y = mOrigin.y + ((rand() % 100) - 50) / 50;
				//set moving
				mPatrolling = true;
				//reset timer
				mPatrolTimer = mPatrolTime;
			}
			else {
				//std::cout << "Patrolling" << std::endl;
				//if moving, move to destination
				UpdatePhysics(Frametime);
				//decrement timer
				mPatrolTimer -= Frametime;
				//if timer reaches 0, set not moving
				//if arrived at destination, set moving false
				if (mPatrolTimer <= 0) {
					mPatrolling = false;
				}
			}
			//check for player proximity
			vec2D playerPos = vec2D();
			bool check = false;
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				//std::cout << "Prox Check" << std::endl;
				if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Player")
				{
					//std::cout << "Found Player" << std::endl;
					check = true;
					playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
					
				}
			}
			//if player moves within x radius, set mode to moving
			if (check && distance(playerPos, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetPos()) < 5.0f) {
				//std::cout << "Player Detected" << std::endl;
				mState = EnemyState::Moving;
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Gate")
					{
						auto& logic = p_ecs.GetComponent<Logic>(i);
						dynamic_cast<GateController*>(logic.GetScriptByName("GateController"))->enemies += 1;
					}
				}
			}
		}
		if (mState == EnemyState::Moving) {
			//std::cout << "Chasing Player" << std::endl;
			//if moving, move to attack player
			UpdatePhysics(Frametime);
			mAttackCooldown -= Frametime;
		}
		if (mState == EnemyState::Attacking) {
			//std::cout << "Attacking" << std::endl;
			//if moving, move to attack player
			UpdatePhysics(Frametime);
			mAttackCooldown -= Frametime;
			mAttackTime -= Frametime;
		}
	/*	if (mState == EnemyState::Death)
		{*/
			//p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blank");
			//std::cout << std::to_string(static_cast<int>(mState)) << std::endl;
		//}
		Animate(mState);
	}

	void EnemyMovement::End() {
		delete this;
	}

	void EnemyMovement::UpdatePhysics(float Frametime)
	{
		if (mState != EnemyState::Death)
		{
			auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
			auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
			if (mState == EnemyState::Patrolling) {
				rigidbody.SetDir(mDest.x - transform.GetPos().x, mDest.y - transform.GetPos().y);
				vec2D newVel = vec2D(0, 0);
				newVel = rigidbody.GetVel();
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetUVCoor().x = 512.0f;
				newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
				newVel = mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
				if (newVel.x > -99 && newVel.y < 99) {
					rigidbody.SetVel(newVel);
				}
				vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
				rigidbody.SetNextPos(nextPos);
			}
			else {
				float dist = 0;
				if (mState == EnemyState::Moving) {
					for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
					{
						if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Player")
						{
							rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
							vec2D newVel = vec2D(0, 0);
							newVel = rigidbody.GetVel();
							p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetUVCoor().x = 512.0f;
							newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
							newVel = mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
							if (newVel.x > -99 && newVel.y < 99) {
								rigidbody.SetVel(newVel);
							}
							vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
							rigidbody.SetNextPos(nextPos);

							dist = distance(transform.GetPos(), p_ecs.GetComponent<Transform>(i).GetPos());
							if (dist < 0.1f)
							{
								//std::cout << "In Proximity1" << std::endl;
								//if within range to attack, set mode to attacking
								mState = EnemyState::Attacking;
							}
						}
					}
				}
				//Attack Range
				//check if within range. If not, set to moving state
				if (dist < 0.1f)
				{
					//std::cout << "In Proximity2" << std::endl;
					//if within range to attack, set mode to attacking
					mState = EnemyState::Attacking;
				}
				else {
					//std::cout << "Out of range" << std::endl;
					mState = EnemyState::Moving;
				}
				if (mState == EnemyState::Attacking) {
					//if attacking, attack and calculate chances for cooldown
					if (mAttackCooldown <= 0 && (rand() % 100) <= 80) {
						mAttackCooldown = 10.0f;
						mAttackTime = 10.0f;
						mState = EnemyState::Moving;
						//std::cout << "Cooldown" << std::endl;
						//if on cooldown, check if can retreat
						//if can retreat, retreat.
						//set to moving state after retreat
					}
					if (mAttackCooldown <= 0) {
						mAttackTime = 10.0f;
					}
					vec2D newVel = vec2D();
					if (mAttackCooldown > 0.0f && mAttackTime <= 0.0f && mState != EnemyState::Death)
					{
						newVel -= newVel * 2;
						p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetUVCoor().x = -512.0f;
						mState = EnemyState::Moving;
					}
					else {
						newVel = (mPhys.friction(newVel, Frametime));
					}
					if (newVel.x > -99 && newVel.y < 99) {
						rigidbody.SetVel(newVel);
					}
					vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
					rigidbody.SetNextPos(nextPos);
				}
				auto pCol = p_ecs.GetComponent<Collider>(GetScriptEntityID()).GetCollisionArray();
				if (mAttackTime > 0) {
					(pCol + 1)->is_Alive = true;
					//std::cout << "Attack Active" << std::endl;
				}
				else {
					(pCol + 1)->is_Alive = false;
				}
			}
		}
	}

	void EnemyMovement::Animate(EnemyState state)
	{
		if (mState != EnemyState::Death)
		{
			switch (state)
			{
			case EnemyState::Patrolling:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeIdle");
				break;
			case EnemyState::Moving:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeIdle");
				break;
			case EnemyState::Attacking:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeAttack");
				break;
				/*	case EnemyState::Death:
						p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeDeath");*/

			}
		}
		else
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeDeath");
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Gate")
				{
					auto& logic = p_ecs.GetComponent<Logic>(i);
					dynamic_cast<GateController*>(logic.GetScriptByName("GateController"))->enemies -= 1;
				}
			}
		}
	}

	void EnemyMovement::SetState(EnemyState state)
	{
		mState = state;
	}

	std::string EnemyMovement::GetScriptName() {
		return "EnemyMovement";
	}

	
}
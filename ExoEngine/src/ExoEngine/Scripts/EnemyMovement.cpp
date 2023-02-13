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

namespace EM
{
	/*!*************************************************************************
	Ctor for new Enemy Movement Scripts
	****************************************************************************/
	EnemyMovement::EnemyMovement() : mState{}, mAttackCooldown { 0.0f }, mAttackTime{ 0.0f } {}

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
	void EnemyMovement::Start() {}

	/*!*************************************************************************
	Update loop for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Update(float Frametime)
	{
		if (mState != EnemyState::Death)
		{
			mAttackCooldown -= Frametime;
			mAttackTime -= Frametime;
			UpdateState();
			UpdateAttack();
			UpdatePhysics(Frametime);
		}
		else {
			Animate(mState);
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blank");
			//std::cout << std::to_string(static_cast<int>(mState)) << std::endl;
		}
	}

	void EnemyMovement::UpdateState()
	{
		if ((mAttackCooldown <= 0.0f) && (mState != EnemyState::Death))
		{
			mState = EnemyState::Idle;
		}
	}

	void EnemyMovement::UpdateAttack()
	{
		auto pCol = p_ecs.GetComponent<Collider>(GetScriptEntityID()).GetCollisionArray();
		if (mState == EnemyState::Attacking)
		{
			(pCol + 1)->is_Alive = true;
		}
		else
		{
			(pCol + 1)->is_Alive = false;
		}
	}

	void EnemyMovement::UpdatePhysics(float Frametime)
	{
		if (mState != EnemyState::Death)
		{
			auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
			auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.HaveComponent<Tag>(i) && !std::strcmp(p_ecs.GetComponent<Tag>(i).GetTag().c_str(), "Player"))
				{
					rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
				}
			}
			vec2D newVel = vec2D(0, 0);
			newVel = rigidbody.GetVel();
			if (squarelength(rigidbody.GetDir()) < 100.0f)
			{
				if (mAttackCooldown <= 0.0f)
				{
					mState = EnemyState::Moving;
				}
				else if (mState != EnemyState::Death)
				{
					mState = EnemyState::Attacking;
				}
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetUVCoor().x = 512.0f;
				newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
				newVel = mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
				//Attack Range
				if (squarelength(rigidbody.GetDir()) < 6.0f)
				{
					//Attack Logic Here
					if (mAttackTime > 0.0f)
					{
						mAttackCooldown = 2.5f;
					}
					if (mAttackCooldown <= 0.0f)
					{
						mAttackTime = 2.0f;
					}
				}
			}
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
	}

	void EnemyMovement::Animate(EnemyState state)
	{
		if (mState != EnemyState::Death)
		{
			switch (state)
			{
			case EnemyState::Idle:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeIdle");
				break;
			case EnemyState::Moving:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeIdle");
				break;
			case EnemyState::Attacking:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeAttack");
				break;
			case EnemyState::Death:
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeDeath");
				break;
			}
		}
		else
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("MeleeDeath");
		}
	}

	void EnemyMovement::SetState(EnemyState state)
	{
		mState = state;
	}

	/*!*************************************************************************
	End of Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::End() 
	{
		delete this;
	}

	/*!*************************************************************************
	Returns the name of the script
	****************************************************************************/
	std::string EnemyMovement::GetScriptName() { return "EnemyMovement"; }
}
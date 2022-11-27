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

****************************************************************************
***/

#include "EnemyMovement.h"

namespace EM
{
	EnemyMovement::EnemyMovement() : mAttackCooldown{ 0.0f } {};

	EnemyMovement* EnemyMovement::Clone() const
	{
		return new EnemyMovement(*this);
	}
	void EnemyMovement::Start() {}

	void EnemyMovement::Update(float Frametime)
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
		vec2D newVel = vec2D(0,0);
		newVel = rigidbody.GetVel();
		if (mAttackCooldown <= 0.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Idle");
		}
		if (squarelength(rigidbody.GetDir()) < 3.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Running");
			newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
			newVel = mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
			//Attack Range
			if (squarelength(rigidbody.GetDir()) < 0.1f)
			{
				//Attack Logic Here
				mAttackCooldown = 2.5f;
				p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("CA1");
			}
		}
		if (mAttackCooldown > 0.0f)
		{
			p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Running");
			newVel -= newVel * 2;
		}
		else {
			newVel = (mPhys.friction(newVel, Frametime));
		}
		if (newVel.x > -99 && newVel.y < 99) {
			rigidbody.SetVel(newVel);
		}
		vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
		rigidbody.SetNextPos(nextPos);
		mAttackCooldown -= Frametime;
	}

	void EnemyMovement::End() 
	{
		delete this;
	}

	std::string EnemyMovement::GetScriptName() { return "EnemyMovement"; }
}
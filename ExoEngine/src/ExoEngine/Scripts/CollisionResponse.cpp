/*!*****************************************************************************
\file CollisionResponse.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 27-11-2022
\brief  This file contains the function definitions for the collision response
		script
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "CollisionResponse.h"
#include "PlayerController.h"
#include "EnemyMovement.h"
#include "SkillsChest.h"

namespace EM
{
	/*!*************************************************************************
	This function clones the script by allocating and constructing a copy of this 
	script and returning it
	****************************************************************************/
	CollisionResponse* CollisionResponse::Clone() const
	{
		 return new CollisionResponse(*this);
	}
	/*!*************************************************************************
	This function initialises the script. As there are no data members that require
	initialization, this function is empty
	****************************************************************************/
	void CollisionResponse::Start() {}
	/*!*************************************************************************
	This function runs the logic of the script to check for collision and apply
    a counter-force to the entity's current velocity which is calculated based on
    the current velocity and the collision normal
	****************************************************************************/
	void CollisionResponse::Update(float Frametime)
	{
		UNREFERENCED_PARAMETER(Frametime);
		auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
		//auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		//auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
		//auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
		//auto& attrib = p_ecs.GetComponent<Attributes>(GetScriptEntityID());

		//std::cout << &col << "\n";

		//Taking Damage As Player
		if (tag.GetNameTag() == "player")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				auto& playerstats = p_ecs.GetComponent<PlayerAttributes>(GetScriptEntityID());
				if (playerstats.mDamageCoolDown <= 0.0f)
				{
					playerstats.mIsDamaged = true;
				}
			}
		}
		//Enemy Taking Damage
		if (tag.GetNameTag() == "Enemy")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				auto& enemystats = p_ecs.GetComponent<EnemyAttributes>(GetScriptEntityID());
				if (enemystats.mDamageCoolDownTimer <= 0.0f)
				{
					enemystats.mIsDamaged = true;
				}
			}
		}

		if (p_ecs.HaveComponent<Tag>(GetScriptEntityID()) && p_ecs.GetComponent<Tag>(GetScriptEntityID()).GetTag() == "Enemy")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				auto& enemystats = p_ecs.GetComponent<EnemyAttributes>(GetScriptEntityID());
				if (enemystats.mDamageCoolDownTimer <= 0.0f)
				{
					enemystats.mIsDamaged = true;
				}
			}
		}
		//if chest is damaged
		/*if (tag.GetNameTag() == "SkillsChest")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				dynamic_cast<SkillsChest*>(logic.GetScriptByName("SkillsChest"))->SetState(SkillsChest::ChestState::Dead);
				dynamic_cast<SkillsChest*>(logic.GetScriptByName("SkillsChest"))->Animate(SkillsChest::ChestState::Dead);
				vec2D response = rigidbody.GetVel();
				vec2D normal = col.GetCollisionArray()[0].mCollisionNormal;
			}
		}*/
	}
	/*!*************************************************************************
	This function ends the script by deleting the pointer to this script
	****************************************************************************/
	void CollisionResponse::End()
	{
		delete this;
	}
	/*!*************************************************************************
	This function returns the purpose of the script as a flag for when it is called
	****************************************************************************/
	std::string CollisionResponse::GetScriptName() { return "CollisionResponse"; }
}
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
		//auto& att = p_ecs.GetComponent<Attributes>(GetScriptEntityID());
		auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
		auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());

		auto& attrib = p_ecs.GetComponent<Attributes>(GetScriptEntityID());

		//std::cout << &col << "\n";
		if (col[0].mHit || col[1].mHit) {
			vec2D response = rigidbody.GetVel();
			vec2D normal = vec2D();
			normal += col[0].mCollisionNormal;
			//Normalize(normal, normal);
			float dotProd = dotProduct(normal, response);
			if (dotProd <= 0) {
				normal = normal * dotProd;
				response -= normal;
				rigidbody.SetVel(response);
			}
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			rigidbody.SetNextPos(nextPos);
			//std::cout << "Next Pos: " << rigidbody.GetNextPos().x << ", " << rigidbody.GetNextPos().y << "\n";
			transform.SetPos(nextPos);
		}

		//Taking Damage As Player
		if (tag.GetNameTag() == "Player")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				if (dynamic_cast<PlayerController*>(logic.GetScriptByName("PlayerController"))->mDamageTimer <= 0.0f)
				{
					dynamic_cast<PlayerController*>(logic.GetScriptByName("PlayerController"))->SetState(PlayerController::PlayerState::Damage);
					dynamic_cast<PlayerController*>(logic.GetScriptByName("PlayerController"))->Animate(PlayerController::PlayerState::Damage);
					dynamic_cast<PlayerController*>(logic.GetScriptByName("PlayerController"))->mIsDamaged = true;
					dynamic_cast<PlayerController*>(logic.GetScriptByName("PlayerController"))->mDamageTimer = 2.5f;
				}
			}
		}
		//Enemy Taking Damage
		if (tag.GetNameTag() == "Enemy")
		{
			if (col.GetCollisionArray()[0].mHit == 2)
			{
				dynamic_cast<EnemyMovement*>(logic.GetScriptByName("EnemyMovement"))->SetState(EnemyMovement::EnemyState::Death);
				dynamic_cast<EnemyMovement*>(logic.GetScriptByName("EnemyMovement"))->Animate(EnemyMovement::EnemyState::Death);
				vec2D response = rigidbody.GetVel();
				vec2D normal = col.GetCollisionArray()[0].mCollisionNormal;

				float dotProd = dotProduct(normal, response);
				if (dotProd <= 0) {
					normal = normal * dotProd;
					response -= normal * 5;
					rigidbody.SetVel(response);
				}
			}
			if (tag.GetNameTag() == "Enemy")
			{
				logic.GetScript()[1]->Update(Frametime);
			}
		}
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
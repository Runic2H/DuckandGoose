/*!*************************************************************************
****
\file EnemyMovement.h
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

#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	/*!*************************************************************************
	Enemy Movement Script
	****************************************************************************/
	class EnemyMovement : public IScript
	{
	public:

		enum class EnemyState
		{
			Patrolling,
			Moving,
			Attacking,
			Dash,
			Death
		};

		/*!*************************************************************************
		Ctor for new Enemy Movement Scripts
		****************************************************************************/
		EnemyMovement();
		/*!*************************************************************************
		Dtor for Enemy Movement Scripts
		****************************************************************************/
		~EnemyMovement() = default;
		/*!*************************************************************************
		returns an instance for a new Enemy Movement Script
		****************************************************************************/
		virtual EnemyMovement* Clone() const override;
		/*!*************************************************************************
		Init for Enemy Movement Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update loop for Enemy Movement Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End of Enemy Movement Script
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of the script
		****************************************************************************/
		virtual std::string GetScriptName() override;

		void UpdatePhysics(float Frametime);

		void Animate(EnemyState state);

		void SetState(EnemyState state);

		EnemyState& GetState()
		{
			return mState;
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		EnemyState mState;
		float mAttackCooldown;
		float mAttackTime;
		entityPhysics mPhys;
		vec2D mOrigin;
		bool mPatrolling;
		vec2D mDest;
		float mPatrolTimer;
		float mPatrolTime;

	public:
		//bool mIsAttacking;
		//bool mIsIdle;
		//bool mIsMoving;
		//bool mIsDashing;
		//bool mIsDamaged;

	};
}
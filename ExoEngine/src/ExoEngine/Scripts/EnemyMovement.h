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

****************************************************************************
***/

#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyMovement : public IScript
	{
	public:
		EnemyMovement();
		~EnemyMovement() = default;
		virtual EnemyMovement* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual std::string GetScriptName() override;
	private:
		float mAttackCooldown;
		entityPhysics mPhys;
	};
}
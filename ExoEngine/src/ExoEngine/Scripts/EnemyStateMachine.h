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
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"
#include "Platform/Logic/StateMachines/StateMachine.h"
#include "Platform/Logic/States/IStates.h"
#include "Platform/Logic/States/EnemyStates/EnemyAttack.h"
#include "Platform/Logic/States/EnemyStates/EnemyChase.h"
#include "Platform/Logic/States/EnemyStates/EnemyDeath.h"
#include "Platform/Logic/States/EnemyStates/EnemyIdle.h"

namespace EM
{

	class EnemyStateMachine : public IScript
	{
	public:
		EnemyStateMachine() : mEnemyStateMachine{ StateMachine(this->GetScriptEntityID()) } {}
		EnemyStateMachine(Entity entity) : mEnemyStateMachine{ StateMachine(entity) } {}
		~EnemyStateMachine() = default;
		virtual IScript* Clone() const override
		{
			return new EnemyStateMachine(*this);
		}
		virtual void Start() override
		{
			mEnemyStateMachine.ChangeState(new EnemyIdle(&mEnemyStateMachine));
		}
		virtual void Update(float Frametime) override
		{

		}
		virtual void End() override
		{

		}

		virtual std::string GetScriptName() override
		{
			return "EnemyStateMachine";
		}

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		StateMachine mEnemyStateMachine;
	};
}
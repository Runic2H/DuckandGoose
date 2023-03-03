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
#include "Platform/Logic/States/EnemyIdle.h"


namespace EM
{
	/*!*************************************************************************
	Ctor for new Enemy Movement Scripts
	****************************************************************************/
	EnemyMovement::EnemyMovement() {}

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
		mEnemyStateMachine.ChangeState(new EnemyIdle());
	}

	/*!*************************************************************************
	Update loop for Enemy Movement Script
	****************************************************************************/
	void EnemyMovement::Update(float Frametime)
	{
		
	}

	void EnemyMovement::End() {
		delete this;
	}

	std::string EnemyMovement::GetScriptName() {
		return "EnemyMovement";
	}

	
}
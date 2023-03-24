/*!*************************************************************************
****
\file EnemyDeath.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when enemy dies.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyDeath.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDeath::EnemyDeath(StateMachine* stateMachine) : mDeathTimer{0.3f} { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* EnemyDeath::HandleInput(StateMachine* stateMachine, const int& key)
	{

		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy dies
	****************************************************************************/
	void EnemyDeath::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 2))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[2].should_play = true;
		}

		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mEnemyType == EnemyAttributes::EnemyTypes::ENEMY_MELEE)
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_DEATH");
		else
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_RANGED_ENEMY_DEATH");

		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = false;

		//player hp regen
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
			{
				//increment player hp based on current player hp
				p_ecs.GetComponent<PlayerAttributes>(i).mHealth += (160 / p_ecs.GetComponent<PlayerAttributes>(i).mHealth); //higher hp will regen less health
				//play hp regen sound
				if (p_ecs.HaveComponent<Audio>(i) && (p_ecs.GetComponent<Audio>(i).GetSize() > 8))
				{
					p_ecs.GetComponent<Audio>(i)[8].should_play = true;
				}
			}
		}
	}

	/*!*************************************************************************
	Update state for when enemy dies
	****************************************************************************/
	void EnemyDeath::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		mDeathTimer -= Frametime;
		if (mDeathTimer <= 0) {
			mDeathTimer = 0;
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;;
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[0].is_Alive = false;
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		}
	}

	/*!*************************************************************************
	Exit state for when enemy dies
	****************************************************************************/
	void EnemyDeath::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = false;
		delete this;
	}
}
/*!*************************************************************************
****
\file BossChase.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the enemy chasing state

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "BossChasing.h"
#include "BossAttack.h"


namespace EM
{
	BossChasing::BossChasing(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossChasing::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is chasing state
	****************************************************************************/
	void BossChasing::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 1.f;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 3.f;

	}

	/*!*************************************************************************
	Update state for when enemy is chasing state
	****************************************************************************/
	void BossChasing::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		float chasingspeed = 2.0f;
		//p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		//p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown -= Frametime;
		for (auto i = 0; i < p_ecs.GetTotalEntities(); i++)
		{
			if (p_ecs.HaveComponent<PlayerAttributes>(i) && p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer > 0.0f)
			{
				if (p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y
					<= p_ecs.GetComponent<Transform>(i).GetPos().y)
				{
					p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y += chasingspeed * Frametime;
				}
			
				
			}
		}

	}

	/*!*************************************************************************
	Exit state for when enemy is chasing state
	****************************************************************************/
	void BossChasing::OnExit(StateMachine* stateMachine)
	{
		//p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
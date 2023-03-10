/*!*************************************************************************
****
\file OnDamaged.cpp
\author Elton Teo Zhe Wei, Cheung Jun Yin Matthew
\par DP email: e.teo@digipen.edu, j.cheung"digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when the player takes damage

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "OnDamaged.h"
#include "OnIdle.h"
#include "OnDieded.h"

namespace EM
{
	OnDamaged::OnDamaged(StateMachine* stateMachine) {}

	IStates* OnDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	/*!*************************************************************************
	Enter state for Player damaged state
	****************************************************************************/
	void OnDamaged::OnEnter(StateMachine* stateMachine)
	{
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Enemy") {
				pDmg = p_ecs.GetComponent<EnemyAttributes>(i).mDamage;
			}
		}
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg;
		/*if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
		{
			stateMachine->ChangeState(new OnDieded(stateMachine));
		}*/
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 0.5f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Damage");

		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 5))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[5].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for Player damaged state
	****************************************************************************/
	void OnDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer -= Frametime;
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
		{
			stateMachine->ChangeState(new OnDieded(stateMachine));
		}
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}

	/*!*************************************************************************
	Exit state for Player damaged state
	****************************************************************************/
	void OnDamaged::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
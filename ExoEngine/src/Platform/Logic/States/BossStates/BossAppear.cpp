/*!*************************************************************************
****
\file BossAppear.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	This file contains the logic for the state when boss first appears

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "BossIdle.h"
#include "BossAppear.h"
namespace EM
{
	BossAppear::BossAppear(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossAppear::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when Boss is appearing state
	****************************************************************************/
	void BossAppear::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EYEBOSS_Idle_1");
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_SpriteSheet = true;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
		//p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetPos({ 6.714.f, 1.0f });
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mEnemyFacing = EnemyAttributes::Facing::LEFT;
		
	}

	/*!*************************************************************************
	Update state for when Boss is appearing state
	****************************************************************************/
	void BossAppear::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		float fallspeed = 2.5f;
		if(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y >= 0)
		{
			vec2D& nextpos = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos();
			nextpos.y -= (fallspeed * Frametime);
		}
		else
			stateMachine->ChangeState(new BossIdle(stateMachine));
	}

	/*!*************************************************************************
	Exit state for when Boss is appearing state
	****************************************************************************/
	void BossAppear::OnExit(StateMachine* stateMachine)
	{
		UNREFERENCED_PARAMETER(stateMachine);
		delete this;
	}
}
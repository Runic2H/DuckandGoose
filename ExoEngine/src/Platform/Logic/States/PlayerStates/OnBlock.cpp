/*!*************************************************************************
****
\file OnBlock.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2450
\par Section: a
\par Assignment GAM200
\date 24/2/2022
\brief	Blocking state for player

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Platform/Graphics/Camera2D.h"
#include "Platform/Graphics/Graphics.h"
#include "OnBlock.h"
#include "OnIdle.h"

float EaseInOutSine(float start, float end, float value)
{
	end -= start;
	return (float)-end * 0.5f * (cosf(M_PI * value) - 1) + start;
}

namespace EM
{
	OnBlock::OnBlock(StateMachine* stateMachine) : mTimer{ 0.0f }, mDuration{ 0.15f }, mCamMinX{ EM::Graphic::camera.GetPosition().x }, mCamMaxX{ EM::Graphic::camera.GetPosition().x + 0.02f },
		mCamMinY{ EM::Graphic::camera.GetPosition().y }, mCamMaxY{ EM::Graphic::camera.GetPosition().y + 0.02f } {UNREFERENCED_PARAMETER(stateMachine); }

	IStates* OnBlock::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for Player Blocking state
	****************************************************************************/
	void OnBlock::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer = 0.5f;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Block");
		}
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 7))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[7].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for Player Blocking state
	****************************************************************************/
	void OnBlock::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer -= Frametime;
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown <= 0.0f)
			{
				if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 3))
				{
					p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[3].should_play = true;
				}

				mTimer += Frametime * 2;
				if (mTimer >= mDuration) {
					mTimer = 0.f;
					std::swap(mCamMinX, mCamMaxX);
					std::swap(mCamMinY, mCamMaxY);
				}

				EM::Graphic::camera.SetPosition({ EaseInOutSine(mCamMinX,mCamMaxX,mTimer / mDuration) , EaseInOutSine(mCamMinY,mCamMaxY,mTimer / mDuration), EM::Graphic::camera.GetPosition().z });

				int pDmg = 0;
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
					if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Enemy") {
						pDmg = p_ecs.GetComponent<EnemyAttributes>(i).mDamage;
					}
				}
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg/5;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown = 2.0f;
			}
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer <= 0)
			{
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown = 5.0f;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsBlocking = false;
				stateMachine->ChangeState(new OnIdle(stateMachine));
			}
		}
		else
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}
	/*!*************************************************************************
	Exit state for Player Blocking state
	****************************************************************************/
	void OnBlock::OnExit(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<PlayerAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown = 5.0f;
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsBlocking = false;
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		}
		delete this;
	}
}
#include "HazardFire.h"
#include "HazardIdle.h"

namespace EM
{
	HazardFire::HazardFire(StateMachine* stateMachine) : mCurrTrans{ vec2D() }, mCurrScale{ vec2D() } {}

	IStates* HazardFire::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void HazardFire::OnEnter(StateMachine* stateMachine)
	{
		mCurrTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos();
		mCurrScale = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale();
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mHazardType == Attributes::HazardTypes::HAZARD_GROUND)
			{
				p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetPos(mCurrTrans.x + -0.015f, mCurrTrans.y + 0.091f);
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Ground_Hazards_Fire");
			}
			if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mHazardType == Attributes::HazardTypes::HAZARD_LASER)
			{
				p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(0.600f, 0.600f);
				p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetPos(mCurrTrans.x + 0.083f, mCurrTrans.y - 0.096f);
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Laser_Hazard_Fire");
			}
		}
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFireDurationTimer = 1.0f;
		}
	}

	void HazardFire::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFireDurationTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFireDurationTimer -= Frametime;
		}
		if (p_ecs.HaveComponent<Collider>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		}
		if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFireDurationTimer <= 0.0f)
		{
			stateMachine->ChangeState(new HazardIdle(stateMachine));
		}
	}

	void HazardFire::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetPos(mCurrTrans.x, mCurrTrans.y);
		p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(mCurrScale.x, mCurrScale.y);
		delete this;
	}
}
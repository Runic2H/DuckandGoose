#include "HazardCharging.h"
#include "HazardFire.h"

namespace EM
{
	HazardCharging::HazardCharging(StateMachine* stateMachine) {}

	IStates* HazardCharging::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void HazardCharging::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mHazardType == Attributes::HazardTypes::HAZARD_GROUND)
			{
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Ground_Hazards_Charging");
			}
			if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mHazardType == Attributes::HazardTypes::HAZARD_LASER)
			{
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Laser_Hazard_Charging");
			}
		}
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFiringCoolDown = 2.0f;
		}
	}

	void HazardCharging::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFiringCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFiringCoolDown -= Frametime;
		}
		if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mFiringCoolDown <= 0.0f)
		{
			stateMachine->ChangeState(new HazardFire(stateMachine));
		}
	}

	void HazardCharging::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
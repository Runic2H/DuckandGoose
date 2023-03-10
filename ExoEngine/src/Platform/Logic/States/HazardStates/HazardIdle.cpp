#include "HazardIdle.h"
#include "HazardCharging.h"

namespace EM
{
	HazardIdle::HazardIdle(StateMachine* stateMachine) {}

	IStates* HazardIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void HazardIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_SpriteSheet = false;
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mChargeCoolDown = 2.0f;
		}
	}

	void HazardIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_ecs.HaveComponent<Attributes>(stateMachine->GetEntityID()))
		{
			p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mChargeCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mChargeCoolDown -=Frametime;
		}
		if (p_ecs.GetComponent<Attributes>(stateMachine->GetEntityID()).mChargeCoolDown <= 0.0f)
		{
			stateMachine->ChangeState(new HazardCharging(stateMachine));
		}
	}

	void HazardIdle::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_SpriteSheet = true;

		delete this;
	}
}
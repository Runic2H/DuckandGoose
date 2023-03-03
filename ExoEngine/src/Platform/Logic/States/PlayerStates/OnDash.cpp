#include "OnDash.h"
#include "OnIdle.h"

namespace EM
{
	OnDash::OnDash(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnDash::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return new OnIdle(stateMachine);
	}
	void OnDash::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Dash");
	}
	void OnDash::OnUpdate(StateMachine* stateMachine, float Frametime)
	{

	}
	void OnDash::OnExit(StateMachine* stateMachine)
	{

	}
}
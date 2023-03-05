#include "OnDieded.h"

namespace EM
{
	OnDieded::OnDieded(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnDieded::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnDieded::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
	}
	void OnDieded::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		//Change Scene to Game Over;
	}
	void OnDieded::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
#include "OnAttack_1.h"
#include "OnIdle.h"

namespace EM
{
	OnAttack_1::OnAttack_1(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnAttack_1::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return new OnIdle(stateMachine);
	}
	void OnAttack_1::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Attack");
	}
	void OnAttack_1::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		std::cout << "Attacking" << std::endl;
	}
	void OnAttack_1::OnExit(StateMachine* stateMachine)
	{
		std::cout << "AttackingExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
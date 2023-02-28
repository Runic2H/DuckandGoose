#include "OnAttack.h"
#include "OnIdle.h"

namespace EM
{
	OnAttack::OnAttack() {}

	IStates* OnAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D)
		{
			return new OnIdle();
		}
		return nullptr;
	}
	void OnAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Attack");
	}
	void OnAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		std::cout << "Attacking" << std::endl;
	}
	void OnAttack::OnExit(StateMachine* stateMachine)
	{
		std::cout << "AttackingExit" << std::endl;
		delete this;
	}
}
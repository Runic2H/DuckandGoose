#include "OnMove.h"
#include "OnAttack.h"

namespace EM
{
	OnMove::OnMove() {}

	IStates* OnMove::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D)
		{
			return new OnAttack();
		}
		return nullptr;
	}
	void OnMove::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Running");
	}
	void OnMove::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		std::cout << "Moving" << std::endl;
	}
	void OnMove::OnExit(StateMachine* stateMachine)
	{
		std::cout << "MovingExit" << std::endl;
		delete this;
	}
}
#include "empch.h"
#include "OnIdle.h"
#include "OnMove.h"

namespace EM
{
	OnIdle::OnIdle() {}

	IStates* OnIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D)
		{
			return new OnMove();
		}
		return nullptr;
	}
	void OnIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Idle");
	}
	void OnIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		std::cout << "Idling" << std::endl;
	}
	void OnIdle::OnExit(StateMachine* stateMachine)
	{
		std::cout << "IdleExit" << std::endl;
		delete this;
	}
}
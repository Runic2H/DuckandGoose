#include "empch.h"
#include "OnIdle.h"
#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnDash.h"

namespace EM
{
	OnIdle::OnIdle(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) && p_Input->KeyHold(key))
		{
			return new OnMove(stateMachine);
		}
		if (key == GLFW_KEY_SPACE)
		{
			return new OnDash(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_LEFT)
		{
			return new OnAttack_1(stateMachine);
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
		stats.mBlockCoolDownTimer -= Frametime;
		stats.mDamageTimer -= Frametime;
	}
	void OnIdle::OnExit(StateMachine* stateMachine)
	{
		std::cout << "IdleExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
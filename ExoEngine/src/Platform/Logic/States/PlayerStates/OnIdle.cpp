#include "empch.h"
#include "OnIdle.h"
#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnDash.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnIdle::OnIdle(StateMachine* stateMachine) {}

	IStates* OnIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) && p_Input->isKeyPressed(key))
		{
			return new OnMove(stateMachine);
		}
		if (key == GLFW_KEY_SPACE && p_Input->isKeyPressed(key) && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown <= 0.0f)
		{
			return new OnDash(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->MousePressed(key))
		{
			return new OnAttack_1(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key) && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown <= 0.0f)
		{
			return new OnBlock(stateMachine);
		}
		return nullptr;
	}
	void OnIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Idle");
	}
	void OnIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown -= Frametime;
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
	}
	void OnIdle::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
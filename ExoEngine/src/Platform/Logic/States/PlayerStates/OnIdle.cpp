#include "empch.h"
#include "OnIdle.h"
#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnDash.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnIdle::OnIdle(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) && p_Input->isKeyPressed(key))
		{
			return new OnMove(stateMachine);
		}
		if (key == GLFW_KEY_SPACE && p_Input->isKeyPressed(key) && stats.mDashCoolDown <= 0.0f)
		{
			return new OnDash(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->MousePressed(key))
		{
			return new OnAttack_1(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key) && stats.mBlockCoolDown <= 0.0f)
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
		std::cout << "Idling" << std::endl;
		stats.mCooldownTimer -= Frametime;
		stats.mBlockCoolDown -= Frametime;
		stats.mDashCoolDown -= Frametime;
		stats.mDamageCoolDown -= Frametime;
		stats.mVel.x = 0.0f;
		stats.mVel.y = 0.0f;
		if (stats.mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
	}
	void OnIdle::OnExit(StateMachine* stateMachine)
	{
		std::cout << "IdleExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
#include "OnAttack_2.h"
#include "OnIdle.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnAttack_2::OnAttack_2(StateMachine* stateMachine) {}

	IStates* OnAttack_2::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->MousePressed(key))
		{
			//return new OnAttack_3(stateMachine);

		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key))
		{
			return new OnBlock(stateMachine);
		}
		return nullptr;
	}
	void OnAttack_2::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Normal_Attack_Swing2");
	}
	void OnAttack_2::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer -= Frametime;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer <= 0.0f)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}
	void OnAttack_2::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
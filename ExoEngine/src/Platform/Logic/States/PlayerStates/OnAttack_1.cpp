#include "OnAttack_1.h"
#include "OnIdle.h"
#include "OnAttack_2.h"
#include "OnBlock.h"

namespace EM
{
	OnAttack_1::OnAttack_1(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnAttack_1::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->MousePressed(key))
		{
			//return new OnAttack_2(stateMachine);

			if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
			{
				p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
				//std::cout << "attacking audio" << std::endl;
			}

		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key))
		{
			return new OnBlock(stateMachine);
		}
		return nullptr;
	}
	void OnAttack_1::OnEnter(StateMachine* stateMachine)
	{
		stats.mCooldownTimer = 0.5f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Attack");


	}
	void OnAttack_1::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mCooldownTimer -= Frametime;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		if (stats.mCooldownTimer <= 0.0f)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
		std::cout << "Attacking" << std::endl;
	}
	void OnAttack_1::OnExit(StateMachine* stateMachine)
	{
		std::cout << "AttackingExit" << std::endl;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
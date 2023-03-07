#include "OnBlock.h"
#include "OnIdle.h"

namespace EM
{
	OnBlock::OnBlock(StateMachine* stateMachine) {}

	IStates* OnBlock::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnBlock::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer = 0.5f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Block");
	}
	void OnBlock::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer -= Frametime;
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged && p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown <= 0.0f)
			{
				int pDmg = 0;
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
					if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Enemy") {
						pDmg = p_ecs.GetComponent<Attributes>(i).GetDamage();
					}
				}
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg/5;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown = 2.0f;
			}
			if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer <= 0)
			{
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown = 5.0f;
				p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsBlocking = false;
				stateMachine->ChangeState(new OnIdle(stateMachine));
			}
		}
		else
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}
	void OnBlock::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockDurationTimer = 2.0f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown = 5.0f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsBlocking = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
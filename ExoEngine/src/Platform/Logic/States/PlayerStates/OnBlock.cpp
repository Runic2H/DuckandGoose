#include "OnBlock.h"
#include "OnIdle.h"

namespace EM
{
	OnBlock::OnBlock(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnBlock::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnBlock::OnEnter(StateMachine* stateMachine)
	{
		stats.mCooldownTimer = 0.5f;
		stats.mBlockDurationTimer = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Block");
	}
	void OnBlock::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		if (p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			stats.mBlockDurationTimer -= Frametime;
			if (stats.mIsDamaged && stats.mDamageCoolDown <= 0.0f)
			{
				int pDmg = 0;
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
					if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Enemy") {
						pDmg = p_ecs.GetComponent<Attributes>(i).GetDamage();
					}
				}
				stats.mHealth -= pDmg/5;
				stats.mDamageCoolDown = 2.0f;
			}
			if (stats.mBlockDurationTimer <= 0)
			{
				stats.mBlockDurationTimer = 2.0f;
				stats.mBlockCoolDown = 5.0f;
				stats.mIsBlocking = false;
				stateMachine->ChangeState(new OnIdle(stateMachine));
			}
		}
		else
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
		std::cout << "Blocking" << std::endl;
	}
	void OnBlock::OnExit(StateMachine* stateMachine)
	{
		std::cout << "BlockingExit" << std::endl;
		stats.mBlockDurationTimer = 2.0f;
		stats.mBlockCoolDown = 5.0f;
		stats.mIsBlocking = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
#include "empch.h"
#include "BossOnDamage.h"
#include "BossChasing.h"
#include "BossDeath.h"

namespace EM
{
	BossOnDamage::BossOnDamage(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossOnDamage::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is damaged state
	****************************************************************************/
	void BossOnDamage::OnEnter(StateMachine* stateMachine)
	{
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player") {
				pDmg = p_ecs.GetComponent<PlayerAttributes>(i).mDamage;
			}
		}
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EYEBOSS_Damaged");
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth -= pDmg;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer = 0.25f;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.20f;

		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 1))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[1].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for when enemy is damaged state
	****************************************************************************/
	void BossOnDamage::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageDurationTimer <= 0) {
			if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mHealth <= 0)
			{
				if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 2))
				{
					p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[2].should_play = true;
				}
				if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 3))
				{
					p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[3].should_play = true;
				}

				stateMachine->ChangeState(new BossDeath(stateMachine));
			}
			else
			{	
				stateMachine->ChangeState(new BossChasing(stateMachine));
			}
		}
	}

	/*!*************************************************************************
	Exit state for when enemy is damaged state
	****************************************************************************/
	void BossOnDamage::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged = false;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer = 0.2f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
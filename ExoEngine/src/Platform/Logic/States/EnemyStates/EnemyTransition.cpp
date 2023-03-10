#include "empch.h"
#include "EnemyTransition.h"
#include "EnemyAttack.h"
#include "EnemyRetreat.h"
#include "EnemyChase.h"

namespace EM
{
	EnemyTransition::EnemyTransition(StateMachine* stateMachine) {}

	IStates* EnemyTransition::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyTransition::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
	}
	void EnemyTransition::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown -= Frametime;
		if ((rand() % 100) <= 80) {
			vec2D playerPos = vec2D();
			bool check = false;
			if (!check)
			{
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
					{
						playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
						check = true;
					}
				}
			}
			if (check && distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 0.1f
				&& p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCoolDown <= 0.0f) {
				stateMachine->ChangeState(new EnemyAttack(stateMachine));
			}
			else
			{
				stateMachine->ChangeState(new EnemyChase(stateMachine));
			}
		}
		else
		{
			stateMachine->ChangeState(new EnemyRetreat(stateMachine));
		}
	}
	void EnemyTransition::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
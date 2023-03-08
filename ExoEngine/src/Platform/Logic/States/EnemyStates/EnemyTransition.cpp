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
		std::cout << "Enemy Attack Transition\n";
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
		if ((rand() % 100) <= 80) {
			vec2D playerPos = vec2D();
			bool check = false;
			if (!check)
			{
				for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
				{
					if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player")
					{
						playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
						check = true;
					}
				}
			}
			if (check && distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 0.1f) {
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
	void EnemyTransition::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown -= Frametime;
	}
	void EnemyTransition::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
#include "empch.h"
#include "EnemyIdle.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyDamaged.h"

namespace EM
{
	EnemyIdle::EnemyIdle(StateMachine* stateMachine) {}

	IStates* EnemyIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
	}
	void EnemyIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		vec2D playerPos = vec2D();
		bool check = false;
		if (!check)
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				//std::cout << "Prox Check" << std::endl;
				if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
				{
					check = true;
					//std::cout << "Found Player" << std::endl;
					playerPos = p_ecs.GetComponent<Transform>(i).GetPos();

				}
			}
		}
		//if player moves within x radius, set mode to moving
		if (distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 0.4f && check) {
			//std::cout << "Player Detected" << std::endl;
			stateMachine->ChangeState(new EnemyChase(stateMachine));
		}

	}
	void EnemyIdle::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
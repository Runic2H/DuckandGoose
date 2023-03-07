#include "empch.h"
#include "EnemyAttack.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyIdle.h"
#include "EnemyDamaged.h"
#include "EnemyTransition.h"

namespace EM
{
	EnemyAttack::EnemyAttack(StateMachine* stateMachine) {}

	IStates* EnemyAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer = 1.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_ENEMY_MELEE_ATTACKING_SPRITESHEET");
		std::cout << "Enemy Attacking\n";
	}
	void EnemyAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer -= Frametime;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f)
		{
			stateMachine->ChangeState(new EnemyTransition(stateMachine));
		}
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		vec2D playerPos = vec2D();
		bool check = false;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player")
			{
				playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
				check = true;
			}
		}
		if (check && distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) > 0.2f) {
			stateMachine->ChangeState(new EnemyChase(stateMachine));
		}
	}
	void EnemyAttack::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
#include "empch.h"
#include "EnemyIdle.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyDamaged.h"

namespace EM
{
	EnemyIdle::EnemyIdle(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) } {}

	IStates* EnemyIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeIdle");
		std::cout << "Idle Entry" << std::endl;
	}
	void EnemyIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDamageCoolDownTimer -= Frametime;
		stats.mAttackCooldown -= Frametime;
		if (stats.mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		vec2D playerPos = vec2D();
		bool check = false;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			//std::cout << "Prox Check" << std::endl;
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Player")
			{
				//std::cout << "Found Player" << std::endl;
				check = true;
				playerPos = p_ecs.GetComponent<Transform>(i).GetPos();

			}
		}
		//if player moves within x radius, set mode to moving
		if (check && distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 4.0f) {
			//std::cout << "Player Detected" << std::endl;
			stateMachine->ChangeState(new EnemyChase(stateMachine));
		}


		std::cout << "EnemyIdling" << std::endl;
	}
	void EnemyIdle::OnExit(StateMachine* stateMachine)
	{
		std::cout << "IdleExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
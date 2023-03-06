#include "empch.h"
#include "EnemyDamaged.h"
#include "EnemyDeath.h"
#include "EnemyIdle.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDamaged::EnemyDamaged(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) } {}

	IStates* EnemyDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyDamaged::OnEnter(StateMachine* stateMachine)
	{
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Player") {
				pDmg = p_ecs.GetComponent<Attributes>(i).GetDamage();
			}
		}
		stats.mHealth -= pDmg;
		if (stats.mHealth <= 0)
		{
			stateMachine->ChangeState(new EnemyDeath(stateMachine));
		}
		stats.mDamageDurationTimer = 0.5f;
		stats.mDamageCoolDownTimer = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Damage");
	}
	void EnemyDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDamageDurationTimer -= Frametime;
		if (stats.mDamageDurationTimer <= 0) {
			stateMachine->ChangeState(new EnemyIdle(stateMachine));
		}
	}
	void EnemyDamaged::OnExit(StateMachine* stateMachine)
	{
		stats.mIsDamaged = false;
		std::cout << "Death Animation Exit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
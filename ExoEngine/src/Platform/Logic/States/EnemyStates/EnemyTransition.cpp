#include "EnemyTransition.h"
#include "EnemyAttack.h"
#include "EnemyRetreat.h"

namespace EM
{
	EnemyTransition::EnemyTransition(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) } {}

	IStates* EnemyTransition::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyTransition::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeIdle");
		if ((rand() % 100) <= 80) {
			stateMachine->ChangeState(new EnemyAttack(stateMachine));
		}
		else
		{
			stateMachine->ChangeState(new EnemyRetreat(stateMachine));
		}
	}
	void EnemyTransition::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDamageCoolDownTimer -= Frametime;
		stats.mAttackCooldown -= Frametime;
	}
	void EnemyTransition::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
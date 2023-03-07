#include "EnemyTransition.h"
#include "EnemyAttack.h"
#include "EnemyRetreat.h"

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
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown -= Frametime;
	}
	void EnemyTransition::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
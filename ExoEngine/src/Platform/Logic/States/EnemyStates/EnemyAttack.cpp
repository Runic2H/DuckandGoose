#include "empch.h"
#include "EnemyAttack.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"
#include "EnemyIdle.h"
#include "EnemyDamaged.h"
#include "EnemyTransition.h"

namespace EM
{
	EnemyAttack::EnemyAttack(StateMachine* stateMachine) : mAttackCooldown{ 0.0f }, mAttackTime{ 0.0f }, stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) } {}

	IStates* EnemyAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyAttack::OnEnter(StateMachine* stateMachine)
	{
		stats.mAttackTimer = 1.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeAttack");
	}
	void EnemyAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDamageCoolDownTimer -= Frametime;
		stats.mAttackTimer -= Frametime;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
		if (stats.mAttackTimer <= 0.0f)
		{
			stateMachine->ChangeState(new EnemyTransition(stateMachine));
		}
		if (stats.mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
	}
	void EnemyAttack::OnExit(StateMachine* stateMachine)
	{
		stats.mAttackCooldown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		std::cout << "AttackExit" << std::endl;
		delete this;
	}
}
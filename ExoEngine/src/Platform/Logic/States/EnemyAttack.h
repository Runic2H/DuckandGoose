#pragma once
#include "IStates.h"

namespace EM
{
	class EnemyAttack : public IStates
	{
	public:
		EnemyAttack();
		virtual ~EnemyAttack() = default;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		float mAttackCooldown;
		float mAttackTime;
	};
}
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyDeath : public IStates
	{
	public:
		EnemyDeath();
		virtual ~EnemyDeath() = default;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		float deathTime;
	};
}
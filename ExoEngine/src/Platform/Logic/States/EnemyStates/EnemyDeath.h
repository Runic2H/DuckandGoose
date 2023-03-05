#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyDeath : public IStates
	{
	public:
		EnemyDeath(StateMachine* stateMachine);
		virtual ~EnemyDeath() = default;
		IStates* HandleInput(StateMachine* stateMachine, const int& key);
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		float deathTime;
	};
}
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyNotActive : public IStates
	{
	public:
		EnemyNotActive(StateMachine* stateMachine);
		virtual ~EnemyNotActive() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	};
}
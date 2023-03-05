#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyIdle : public IStates
	{
	public:
		EnemyIdle(StateMachine* stateMachine);
		virtual ~EnemyIdle() = default;
		IStates* HandleInput(StateMachine* stateMachine, const int& key);
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	};
}
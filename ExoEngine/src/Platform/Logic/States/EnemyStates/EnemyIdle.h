#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class EnemyIdle : public IStates
	{
	public:
		EnemyIdle();
		virtual ~EnemyIdle() = default;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	};
}
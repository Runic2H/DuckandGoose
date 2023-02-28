#pragma once
#include "IStates.h"

namespace EM
{
	class OnAttack : public IStates
	{
	public:
		OnAttack();
		virtual ~OnAttack() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	};
}
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class OnAttack_1 : public IStates
	{
	public:
		OnAttack_1(StateMachine* stateMachine);
		virtual ~OnAttack_1() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		PlayerAttributes& stats;
	};
}
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class OnAttack_2 : public IStates
	{
	public:
		OnAttack_2(StateMachine* stateMachine);
		virtual ~OnAttack_2() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		PlayerAttributes& stats;
	};
}

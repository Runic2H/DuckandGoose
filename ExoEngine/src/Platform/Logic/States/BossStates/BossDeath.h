#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class BossDeath : public IStates
	{
	public:
		BossDeath(StateMachine* stateMachine);
		virtual ~BossDeath() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		float mDeathTimer;
	};
}
#pragma once
#include "Platform/Logic/States/IStates.h"

namespace EM
{
	class HazardFire : public IStates
	{
	public:
		HazardFire(StateMachine* stateMachine);
		virtual ~HazardFire() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;

		vec2D mCurrTrans;
		vec2D mCurrScale;
	};
}
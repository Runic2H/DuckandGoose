#pragma once
#include "Platform/Logic/States/IStates.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyChase : public IStates
	{
	public:
		EnemyChase(StateMachine* stateMachine);
		virtual ~EnemyChase() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	};
}
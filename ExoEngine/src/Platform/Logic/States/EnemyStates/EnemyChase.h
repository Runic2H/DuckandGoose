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
		IStates* HandleInput(StateMachine* stateMachine, const int& key);
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		entityPhysics mPhys;
	};
}
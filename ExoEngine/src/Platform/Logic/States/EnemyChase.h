#pragma once
#include "IStates.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyChase : public IStates
	{
	public:
		EnemyChase();
		virtual ~EnemyChase() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) override;
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		entityPhysics mPhys;
	};
}
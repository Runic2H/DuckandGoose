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
		virtual void OnEnter(StateMachine* stateMachine) override;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) override;
		virtual void OnExit(StateMachine* stateMachine) override;
	private:
		entityPhysics mPhys;
	};
}
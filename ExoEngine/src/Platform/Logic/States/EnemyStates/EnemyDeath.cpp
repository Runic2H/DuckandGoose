#include "empch.h"
#include "EnemyDeath.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDeath::EnemyDeath(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) }, mDeathTimer{2.0f} {}

	IStates* EnemyDeath::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyDeath::OnEnter(StateMachine* stateMachine)
	{
		stats.mIsAlive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeDeath");
	}
	void EnemyDeath::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		mDeathTimer -= Frametime;
		if (mDeathTimer <= 0) {
			mDeathTimer = 0;
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[0].is_Alive = false;
			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		}
	}
	void EnemyDeath::OnExit(StateMachine* stateMachine)
	{
		std::cout << "Death Animation Exit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
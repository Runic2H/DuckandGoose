#include "empch.h"
#include "EnemyAttack.h"
#include "EnemyChase.h"

namespace EM
{
	OnIdle::OnIdle() {}

	IStates* OnIdle::HandleInput(StateMachine* stateMachine, const int& key)
	{
		//if take damage, go into damaged state
	}
	void OnIdle::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeAttack");
	}
	void OnIdle::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		//if attacking, attack and calculate chances for cooldown
		if (mAttackCooldown <= 0 && (rand() % 100) <= 80) {
			mAttackCooldown = 10.0f;
			mAttackTime = 10.0f;
			//std::cout << "Cooldown" << std::endl;
			//if on cooldown, check if can retreat
			//if can retreat, retreat.
			//set to moving state after retreat
		}
		if (mAttackCooldown <= 0) {
			mAttackTime = 10.0f;
		}
		auto pCol = p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray();
		if (mAttackTime > 0) {
			(pCol + 1)->is_Alive = true;
			//std::cout << "Attack Active" << std::endl;
		}
		else {
			(pCol + 1)->is_Alive = false;
		}
	}
	void OnIdle::OnExit(StateMachine* stateMachine)
	{
		std::cout << "IdleExit" << std::endl;
		delete this;
	}
}
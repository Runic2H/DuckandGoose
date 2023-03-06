#include "empch.h"
#include "EnemyAttack.h"
#include "EnemyChase.h"
#include "EnemyDeath.h"

namespace EM
{
	EnemyAttack::EnemyAttack(StateMachine* stateMachine) : mAttackCooldown{ 0.0f }, mAttackTime{ 0.0f } {}

	IStates* EnemyAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeAttack");
	}
	void EnemyAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		auto& attrib = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID());
		//if attacking, attack and calculate chances for cooldown
		if (mAttackCooldown <= 0 && (rand() % 100) <= 80) {
			mAttackCooldown = attrib.mDamageCooldownTimer;
			mAttackTime = attrib.mAttackTimer;
			//std::cout << "Cooldown" << std::endl;
			//if on cooldown, check if can retreat
			//if can retreat, retreat.
			//set to moving state after retreat
		}
		if (mAttackCooldown <= 0 && mAttackTime <= 0) {
			mAttackTime = attrib.mAttackTimer;
		}
		auto pCol = p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray();
		vec2D playerPos = vec2D();
		bool check = false;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			//std::cout << "Prox Check" << std::endl;
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player")
			{
				//std::cout << "Found Player" << std::endl;
				check = true;
				playerPos = p_ecs.GetComponent<Transform>(i).GetPos();

			}
		}
		if (mAttackTime > 0) {
			(pCol + 1)->is_Alive = true;
			mAttackTime -= Frametime;
			std::cout << "Attack Cooldown" << mAttackCooldown << std::endl;
			std::cout << "Attack Timer" << mAttackTime << std::endl;
		}
		else {
			(pCol + 1)->is_Alive = false;
		}
		//if player moves within x radius, set mode to moving
		if (check && distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) > 0.1f) {
			//std::cout << "Player Detected" << std::endl
			(pCol + 1)->is_Alive = false;
			stateMachine->ChangeState(new EnemyChase(stateMachine));
		}
		//death
		if (attrib.mHealth <= 0) {
			attrib.mHealth = 0;
			(pCol + 1)->is_Alive = false;
			(pCol)->is_Alive = false;
			stateMachine->ChangeState(new EnemyDeath(stateMachine));
		}
		mAttackCooldown -= Frametime;
		std::cout << "Attack State" << std::endl;
	}
	void EnemyAttack::OnExit(StateMachine* stateMachine)
	{
		std::cout << "AttackExit" << std::endl;
		delete this;
	}
}
#include "empch.h"
#include "EnemyRetreat.h"
#include "EnemyIdle.h"
#include "EnemyDamaged.h"
#include "EnemyChase.h"

namespace EM
{
	EnemyRetreat::EnemyRetreat(StateMachine* stateMachine) {}

	IStates* EnemyRetreat::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyRetreat::OnEnter(StateMachine* stateMachine)
	{
		std::cout << "Enemy Retreating\n";
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeIdle");
	}
	void EnemyRetreat::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		auto& transform = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "Player")
			{
				rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
				vec2D newVel = vec2D(0, 0);
				newVel = rigidbody.GetVel();
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetUVCoor().x = 512.0f;
				newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
				newVel = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
				if (newVel.x > -99 && newVel.y < 99) {
					rigidbody.SetVel(newVel);
				}
				vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
				rigidbody.SetNextPos(nextPos);
			}
		}
		stateMachine->ChangeState(new EnemyChase(stateMachine));
	}
	void EnemyRetreat::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
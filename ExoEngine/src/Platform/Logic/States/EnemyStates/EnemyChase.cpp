#include "empch.h"
#include "EnemyChase.h"
#include "EnemyAttack.h"
#include "EnemyDeath.h"
#include "EnemyDamaged.h"

namespace EM
{
	EnemyChase::EnemyChase(StateMachine* stateMachine) {}

	IStates* EnemyChase::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyChase::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EXOMATA_MELEE_ENEMY_HOVERING");
	}
	void EnemyChase::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mDamageCoolDownTimer -= Frametime;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown -= Frametime;
		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new EnemyDamaged(stateMachine));
		}
		std::cout << "Enemy Chasing" << std::endl;
		float dist = 0;
		auto& transform = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player")
			{
				rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
				//vec2D newVel = vec2D(0, 0);
				vec2D newVel = rigidbody.GetVel();
				p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetUVCoor().x = 512.0f;
				newVel = rigidbody.GetDir() * length(rigidbody.GetAccel()) / 2.f;
				newVel = p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mPhys.accelent(rigidbody.GetVel(), newVel, Frametime);
				if (newVel.x > -99 && newVel.y < 99) {
					rigidbody.SetVel(newVel);
				}
				vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
				rigidbody.SetNextPos(nextPos);

				dist = distance(transform.GetPos(), p_ecs.GetComponent<Transform>(i).GetPos());
			}
		}
		//Attack Range
		//check if within range. If not, set to moving state
		if (dist < 0.1f && p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackCooldown <= 0.0f)
		{
			//std::cout << "In Proximity2" << std::endl;
			//if within range to attack, set mode to attacking
			stateMachine->ChangeState(new EnemyAttack(stateMachine));
		}

	}
	void EnemyChase::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		std::cout << "ChaseExit" << std::endl;
		delete this;
	}
}
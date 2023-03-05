#include "OnDamaged.h"
#include "OnIdle.h"
#include "OnDieded.h"

namespace EM
{
	OnDamaged::OnDamaged(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnDamaged::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnDamaged::OnEnter(StateMachine* stateMachine)
	{
		int pDmg = 0;
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Enemy") {
				pDmg = p_ecs.GetComponent<Attributes>(i).GetDamage();
			}
		}
		stats.mHealth -= pDmg;
		if (stats.mHealth <= 0)
		{
			stateMachine->ChangeState(new OnDieded(stateMachine));
		}
		stats.mDamageDurationTimer = 0.5f;
		stats.mDamageCoolDown = 2.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Damage");
	}
	void OnDamaged::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDamageDurationTimer -= Frametime;
		if (stats.mDamageDurationTimer <= 0)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
		std::cout << "Damaged" << std::endl;
	}
	void OnDamaged::OnExit(StateMachine* stateMachine)
	{
		std::cout << "DamageExit" << std::endl;
		stats.mIsDamaged = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
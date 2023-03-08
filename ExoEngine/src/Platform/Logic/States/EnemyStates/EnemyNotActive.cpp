#include "empch.h"
#include "EnemyNotActive.h"
#include "EnemyIdle.h"

namespace EM
{
	EnemyNotActive::EnemyNotActive(StateMachine* stateMachine) {}

	IStates* EnemyNotActive::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyNotActive::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<EnemyAttributes>(stateMachine->GetEntityID())) {
			p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = false;
		}
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
	}
	void EnemyNotActive::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		vec2D playerPos = vec2D();
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			//std::cout << "Prox Check" << std::endl;
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player")
			{
				//std::cout << "Found Player" << std::endl;
				playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
			}
		}
		//if player moves within x radius, set mode to moving
		if (distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 0.5f) {
			p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = true;
			stateMachine->ChangeState(new EnemyIdle(stateMachine));
		}
	}
	void EnemyNotActive::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
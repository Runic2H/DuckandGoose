#include "EnemyNotActive.h"
#include "EnemyIdle.h"

namespace EM
{
	EnemyNotActive::EnemyNotActive(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()) } {}

	IStates* EnemyNotActive::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyNotActive::OnEnter(StateMachine* stateMachine)
	{
		stats.mIsAlive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
		std::cout << "InActive Entry" << std::endl;
	}
	void EnemyNotActive::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		vec2D playerPos = vec2D();
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			//std::cout << "Prox Check" << std::endl;
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Player")
			{
				//std::cout << "Found Player" << std::endl;
				playerPos = p_ecs.GetComponent<Transform>(i).GetPos();
			}
		}
		//if player moves within x radius, set mode to moving
		if (distance(playerPos, p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos()) < 5.0f) {
			stats.mIsAlive = true;
			stateMachine->ChangeState(new EnemyIdle(stateMachine));
		}
		std::cout << "EnemyNotActive" << std::endl;
	}
	void EnemyNotActive::OnExit(StateMachine* stateMachine)
	{
		std::cout << "Active" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
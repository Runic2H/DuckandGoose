#include "empch.h"
#include "GateUnlocked.h"
#include "GateLocked.h"

namespace EM
{
	GateUnlocked::GateUnlocked(StateMachine* stateMachine) {}

	IStates* GateUnlocked::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void GateUnlocked::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[0].is_Alive = false;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
	}
	void GateUnlocked::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<EnemyAttributes>(i))
			{
				if (p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive)
				{
					stateMachine->ChangeState(new GateLocked(stateMachine));
				}
			}
		}
	}
	void GateUnlocked::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
		delete this;
	}
}
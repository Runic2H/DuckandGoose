#include "empch.h"
#include "GateLocked.h"
#include "GateUnlocked.h"

namespace EM
{
	GateLocked::GateLocked(StateMachine* stateMachine) {}

	IStates* GateLocked::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void GateLocked::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("LASERGATE_BG_V2");
        p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[0].is_Alive = true;
        p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = true;
	}
	void GateLocked::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
        int aliveCount{};
        for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
        {
            if (p_ecs.HaveComponent<EnemyAttributes>(i))
            {
                if (p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive)
                {
                    ++aliveCount;
                }
            }
        }
        if (aliveCount == 0)
        {
			stateMachine->ChangeState(new GateUnlocked(stateMachine));
        }
	}
	void GateLocked::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetMaxIndex() - 1;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;
		delete this;
	}
}
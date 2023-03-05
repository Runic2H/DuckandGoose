#include "OnDash.h"
#include "OnIdle.h"

namespace EM
{
	OnDash::OnDash(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnDash::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnDash::OnEnter(StateMachine* stateMachine)
	{
		stats.mDashDurationTimer = 0.2f;
		stats.mDashCoolDown = 3.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Dash");
	}
	void OnDash::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		stats.mDashDurationTimer -= Frametime;
		auto& pRigid = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
		auto& pTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
		stats.mDir = stats.mDir * 25;
		stats.mDir.x *= 5;
		pRigid.SetVel(stats.mPhys.friction(pRigid.GetVel(), Frametime));
		pRigid.SetVel(stats.mPhys.accelent(pRigid.GetVel(), stats.mVel, Frametime));
		vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
		pRigid.SetNextPos(nextPos);
		if (stats.mDashDurationTimer <= 0.0f)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
		std::cout << "Dashing" << std::endl;
	}
	void OnDash::OnExit(StateMachine* stateMachine)
	{
		std::cout << "DashingExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
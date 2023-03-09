#include "empch.h"
#include "OnDash.h"
#include "OnIdle.h"

namespace EM
{
	OnDash::OnDash(StateMachine* stateMachine) {}

	IStates* OnDash::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnDash::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashDurationTimer = 0.2f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown = 3.0f;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Dash");
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 4))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[4].should_play = true;
		}
	}
	void OnDash::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashDurationTimer -= Frametime;
		auto& pRigid = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
		auto& pTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir = p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir * 2.0f;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir.x *= 0.8f;
		pRigid.SetVel(p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mPhys.friction(pRigid.GetVel(), Frametime));
		pRigid.SetVel(p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mPhys.accelent(pRigid.GetVel(), p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir, Frametime));
		vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
		pRigid.SetNextPos(nextPos);
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashDurationTimer <= 0.0f)
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
	}
	void OnDash::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
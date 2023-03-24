#include "empch.h"
#include "BossIdle.h"
#include "BossAppear.h"

namespace EM
{
	BossAppear::BossAppear(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossAppear::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when Boss is not active state
	****************************************************************************/
	void BossAppear::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("BossEyeball");
		p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetPos({ 4.72f, 1.0f });
	}

	/*!*************************************************************************
	Update state for when Boss is not active state
	****************************************************************************/
	void BossAppear::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		//UNREFERENCED_PARAMETER(Frametime);
		float fallspeed = 10.f;
		if(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y >= 0)
		{
			vec2D& nextpos = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos();
			nextpos.y -= (fallspeed * Frametime);
		}
		else
			stateMachine->ChangeState(new BossIdle(stateMachine));
	}

	/*!*************************************************************************
	Exit state for when Boss is not active state
	****************************************************************************/
	void BossAppear::OnExit(StateMachine* stateMachine)
	{
		//p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		//p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = true;
		//p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_SpriteSheet = true;
		//p_ecs.GetComponent<Collider>(stateMachine->GetEntityID())[0].is_Alive = true;
		//p_ecs.GetComponent<Collider>(stateMachine->GetEntityID())[1].is_Alive = false;
		delete this;
	}
}
#include"empch.h"
#include"BossAttack.h"
#include"BossIdle.h"
#include"BossChasing.h"

namespace EM
{
	BossAttack::BossAttack(StateMachine* stateMachine) { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossAttack::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer = 1.0f;
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[0].should_play = true;
		}
	}

	/*!*************************************************************************
	Update state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer -= Frametime;

		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer > 0.f)
		{

			p_ecs.GetComponent<Collider>(stateMachine->GetEntityID())[1].is_Alive = true;
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "RangeLaser")
				{

					p_ecs.GetComponent<Transform>(i).SetPos(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().x - 0.815f,
					p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetPos().y + 0.067f);
					p_ecs.GetComponent<Transform>(i).SetScale(p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale());
					p_ecs.GetComponent<Sprite>(i).SetLayerOrder(5);
				}
			}
		}
		else if(p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f)
		{
			stateMachine->ChangeState(new BossIdle(stateMachine));
		}

	}

	/*!*************************************************************************
	Exit state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnExit(StateMachine* stateMachine)
	{
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Tag>(i) && p_ecs.GetComponent<Tag>(i).GetTag() == "RangeLaser")
			{
				p_ecs.GetComponent<Sprite>(i).SetLayerOrder(6);
				p_ecs.GetComponent<Sprite>(i).GetIndex().x = 0;
			}
		}
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID())[1].is_Alive = false;
		delete this;
	}
}
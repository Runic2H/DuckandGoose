#include"empch.h"
#include"BossAttack.h"
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
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer = 2.0f;
	}

	/*!*************************************************************************
	Update state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer <= 0.0f ? 0.0f : p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer -= Frametime;

		if (p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mAttackTimer > 0.f)
		{
			for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
			{
				if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "BossLaser")
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
			stateMachine->ChangeState(new BossChasing(stateMachine));
		}

	}

	/*!*************************************************************************
	Exit state for when enemy is chasing state
	****************************************************************************/
	void BossAttack::OnExit(StateMachine* stateMachine)
	{
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "BossLaser")
			{
				p_ecs.GetComponent<Sprite>(i).SetLayerOrder(6);
				p_ecs.GetComponent<Sprite>(i).GetIndex().x = 0;
			}
		}
		
		delete this;
	}
}
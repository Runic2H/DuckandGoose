#include "empch.h"
#include "BossDeath.h"
#include "ExoEngine/ECS/SceneManager.h"
namespace EM
{
	BossDeath::BossDeath(StateMachine* stateMachine) : mDeathTimer{ 1.35f } { UNREFERENCED_PARAMETER(stateMachine); }

	IStates* BossDeath::HandleInput(StateMachine* stateMachine, const int& key)
	{
		UNREFERENCED_PARAMETER(stateMachine); UNREFERENCED_PARAMETER(key);
		return nullptr;
	}

	/*!*************************************************************************
	Enter state for when enemy dies
	****************************************************************************/
	void BossDeath::OnEnter(StateMachine* stateMachine)
	{
		if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 2))
		{
			p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[2].should_play = true;
		}

		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("EYEBOSS_Death");

		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[0].is_Alive = false;
		p_ecs.GetComponent<Collider>(stateMachine->GetEntityID()).GetCollisionArray()[1].is_Alive = false;
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = false;
	}

	/*!*************************************************************************
	Update state for when enemy dies
	****************************************************************************/
	void BossDeath::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		mDeathTimer -= Frametime;

		if(p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x == p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetMaxIndex() - 1)
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");

		if (mDeathTimer <= 0.0f) {
			p_Scene->setSceneToLoad("Assets/Scene/Menu.json");
		}

	}

	/*!*************************************************************************
	Exit state for when enemy dies
	****************************************************************************/
	void BossDeath::OnExit(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<EnemyAttributes>(stateMachine->GetEntityID()).mIsAlive = false;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).is_Animated = false;;
		delete this;
	}
}
#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnIdle.h"
#include "OnBlock.h"

namespace EM
{
	OnMove::OnMove(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnMove::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->KeyPressed(key))
		{
			return new OnAttack_1(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->KeyPressed(key))
		{
			return new OnBlock(stateMachine);
		}
		return nullptr;
	}
	void OnMove::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Running");
	}
	void OnMove::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
        if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
            || p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)))
        {
            if (p_Input->KeyHold(GLFW_KEY_W)) {
                stats.mVel.y = 1.0f;
            }
            if (p_Input->KeyHold(GLFW_KEY_S)) {
                stats.mVel.y = -1.0f;
            }
            if (p_Input->KeyHold(GLFW_KEY_D)) {
                stats.mVel.x = 1.0f;
            }
            if (p_Input->KeyHold(GLFW_KEY_A)) {
				stats.mVel.x = -1.0f;
            }
			auto& pRigid = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
			auto& pTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
			if (stats.mVel.x != 0.0f || stats.mVel.y != 0.0f) {
				Normalize(stats.mVel, stats.mVel);
				stats.mVel = stats.mVel * 25;
			}
			pRigid.SetVel(stats.mPhys.friction(pRigid.GetVel(), Frametime));
			pRigid.SetVel(stats.mPhys.accelent(pRigid.GetVel(), stats.mVel, Frametime));
			vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
			pRigid.SetNextPos(nextPos);
        }
		else
		{
			stateMachine->ChangeState(new OnIdle(stateMachine));
		}
		std::cout << "Moving" << std::endl;
	}
	void OnMove::OnExit(StateMachine* stateMachine)
	{
		std::cout << "MovingExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
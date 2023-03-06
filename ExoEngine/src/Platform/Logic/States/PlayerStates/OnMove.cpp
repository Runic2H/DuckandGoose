#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnIdle.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnMove::OnMove(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnMove::HandleInput(StateMachine* stateMachine, const int& key)
	{
		if (key == GLFW_MOUSE_BUTTON_LEFT && p_Input->MousePressed(key))
		{
			return new OnAttack_1(stateMachine);
		}
		if (key == GLFW_MOUSE_BUTTON_RIGHT && p_Input->MousePressed(key))
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
		stats.mCooldownTimer -= Frametime;
		stats.mBlockCoolDown -= Frametime;
		stats.mDashCoolDown -= Frametime;
		stats.mDamageCoolDown -= Frametime;
		vec2D vel{};
		if (stats.mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
		else
		{
			if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
				|| p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)))
			{
				if (p_Input->KeyHold(GLFW_KEY_W)) {
					vel.y = stats.mVel.y;
					std::cout << "Y: " << stats.mVel.y << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_S)) {
					vel.y = -stats.mVel.y;
					std::cout << "Y: " << stats.mVel.y << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_D)) {
					vel.x = stats.mVel.x;
					stats.mDir.x = 1.0f;
					if (p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x < 0)
					{
						p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(-p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x, 
							p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().y);
					}
					std::cout << "X: " << stats.mVel.x << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_A)) {
					vel.x = -stats.mVel.x;
					stats.mDir.x = -1.0f;
					if (p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x > 0)
					{
						p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(-p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x,
							p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().y);
					}
					std::cout << "X: " << stats.mVel.x << std::endl;
				}
				auto& pRigid = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
				auto& pTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
				if (vel.x != 0.0f || vel.y != 0.0f) {
					Normalize(vel, vel);
					vel = vel * 25;
				}
				pRigid.SetVel(stats.mPhys.friction(pRigid.GetVel(), Frametime));
				pRigid.SetVel(stats.mPhys.accelent(pRigid.GetVel(), vel, Frametime));
				vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
				pRigid.SetNextPos(nextPos);
			}
			else
			{
				stateMachine->ChangeState(new OnIdle(stateMachine));
			}
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
#include "OnMove.h"
#include "OnAttack_1.h"
#include "OnIdle.h"
#include "OnBlock.h"
#include "OnDamaged.h"

namespace EM
{
	OnMove::OnMove(StateMachine* stateMachine) {}

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
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mCooldownTimer -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mBlockCoolDown -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDashCoolDown -= Frametime;
		p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDamageCoolDown -= Frametime;
		vec2D vel{};
		if (p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mIsDamaged)
		{
			stateMachine->ChangeState(new OnDamaged(stateMachine));
		}
		else
		{
			if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
				|| p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)))
			{
				if (p_ecs.HaveComponent<Audio>(stateMachine->GetEntityID()) && (p_ecs.GetComponent<Audio>(stateMachine->GetEntityID()).GetSize() > 1))
				{
					p_ecs.GetComponent<Audio>(stateMachine->GetEntityID())[1].should_play = true;
					//std::cout << "moving audio" << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_W)) {
					vel.y = p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mVel.y;
					std::cout << "Y: " << vel.y << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_S)) {
					vel.y = -p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mVel.y;
					std::cout << "Y: " << vel.y << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_D)) {
					vel.x = p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mVel.x;
					p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir.x = 1.0f;
					if (p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x < 0)
					{
						p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(-p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x, 
							p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().y);
					}
					std::cout << "X: " << vel.x << std::endl;
				}
				if (p_Input->KeyHold(GLFW_KEY_A)) {
					vel.x = -p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mVel.x;
					p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mDir.x = -1.0f;
					if (p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x > 0)
					{
						p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).SetScale(-p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().x,
							p_ecs.GetComponent<Transform>(stateMachine->GetEntityID()).GetScale().y);
					}
					std::cout << "X: " << vel.x << std::endl;
				}
				auto& pRigid = p_ecs.GetComponent<RigidBody>(stateMachine->GetEntityID());
				auto& pTrans = p_ecs.GetComponent<Transform>(stateMachine->GetEntityID());
				if (vel.x != 0.0f || vel.y != 0.0f) {
					Normalize(vel, vel);
					vel = vel * 25;
				}
				pRigid.SetVel(p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mPhys.friction(pRigid.GetVel(), Frametime));
				pRigid.SetVel(p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()).mPhys.accelent(pRigid.GetVel(), vel, Frametime));
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
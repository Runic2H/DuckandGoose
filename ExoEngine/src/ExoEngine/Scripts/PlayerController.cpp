#include "PlayerController.h"

namespace EM
{
	PlayerController* PlayerController::Clone() const
	{
		return new PlayerController(*this);
	}

	void PlayerController::Start()
	{
		mState = PlayerState::Idle;
	}

	void PlayerController::Update(float Frametime)
	{
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetEntityID());
        vec2D vel = vec2D();

        if (mCooldownTimer <= 0.0f)
        {
            mState = PlayerState::Idle;
            pRigid.SetVel(mPhys.friction(pRigid.GetVel(), Frametime));
        }

        if (mState == PlayerState::Idle)
        {
            if (p_Input->isKeyPressed(GLFW_KEY_W)) {
                vel.y += 100.f;
                mState = PlayerState::Moving;
            }
            else if (p_Input->isKeyPressed(GLFW_KEY_D)) {
                vel.x += 100.f;
                mState = PlayerState::Moving;
            }
            else if (p_Input->isKeyPressed(GLFW_KEY_S)) {
                vel.y -= 100.f;
                mState = PlayerState::Moving;
            }
            else if (p_Input->isKeyPressed(GLFW_KEY_A)) {
                vel.x -= 100.f;
                mState = PlayerState::Moving;
            }
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && mCooldownTimer <= 0.0f)
        {
            ++mAttackCounter;
            mCooldownTimer = 0.3f;
            mState = PlayerState::Attacking;
        }
        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_RIGHT) && mCooldownTimer <= 0.0f)
        {
            mCooldownTimer = 0.3f;
            mState = PlayerState::Block;
        }


        pRigid.SetVel(mPhys.accelent(pRigid.GetVel(), vel, Frametime));
        vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
        pRigid.SetNextPos(nextPos);

        Animate(mState);
        mCooldownTimer -= Frametime;
	}

    void PlayerController::End()
    {
        delete this;
    }

    std::string PlayerController::GetScriptName()
    {
        return "PlayerController";
    }

    void PlayerController::Animate(PlayerState state)
    {
        switch (state)
        {
        case PlayerState::Idle:
            p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("Idle");
            break;
        case PlayerState::Moving:
            p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("Running");
            break;
        case PlayerState::Attacking:
            if (mAttackCounter == 1)
            {
                p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("CA1");
            }
            else if (mAttackCounter == 2)
            {
                p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("CA2");
            }
            else if (mAttackCounter == 3)
            {
                p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("CA3");
            }
            else if (mAttackCounter == 4)
            {
                p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("CA4");
                mAttackCounter = 0;
            }
            break;
        case PlayerState::Block:
            p_ecs.GetComponent<Sprite>(GetEntityID()).SetTexture("Blocking");
            break;
        }
    }
}
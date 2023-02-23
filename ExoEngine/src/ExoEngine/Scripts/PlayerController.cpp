/*!*************************************************************************
****
\file PlayerController.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Player Controller

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "PlayerController.h"

namespace EM
{

    /*!*************************************************************************
    Default constructor for Player Controller
    ****************************************************************************/
    PlayerController::PlayerController() : mState{ PlayerState::Idle }, mAttackCounter{ 0 }, mCooldownTimer{ 0.0f }, mChargedAttackTimer{ 0.0f }, mDashTimer{0.0f}, mBlockTimer{0.0f},
        mDamageTimer{ 0.0f }, mIsDamaged{ false }, mVel{ vec2D() } {};

    /*!*************************************************************************
    Returns a new copy of PlayerController Script
    ****************************************************************************/
	PlayerController* PlayerController::Clone() const
	{
		return new PlayerController(*this);
	}

    /*!*************************************************************************
    Start State of PlayerController Script
    ****************************************************************************/
	void PlayerController::Start()
	{
		mState = PlayerState::Idle;
	}

    /*!*************************************************************************
    Update Loop of Player Controller Script
    ****************************************************************************/
	void PlayerController::Update(float Frametime)
	{
        mCooldownTimer -= Frametime;
        mDashTimer -= Frametime;
        mBlockTimer -= Frametime;
        mDamageTimer -= Frametime;
        if (mDamageTimer <= 0.0f && mIsDamaged == true)
        {
            mIsDamaged = false;
            for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
            {
                if (p_ecs.GetComponent<NameTag>(i).GetNameTag() == "HPBar")
                {
                    p_ecs.GetComponent<Attributes>(i).GetHealth() -= 10;
                    if (p_ecs.GetComponent<Attributes>(i).GetHealth() <= 0)
                    {
                        p_ecs.GetComponent<Attributes>(i).SetHealth(0);
                    }
                }
            }
        }
        mVel.x = 0.0f;
        mVel.y = 0.0f;

        if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
            || p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)))
        {   
            mCooldownTimer = 0.1f;
            if (p_Input->KeyHold(GLFW_KEY_W)) {
                mVel.y += 50.0f;
                mState = PlayerState::Moving;
            }
            else if (p_Input->KeyHold(GLFW_KEY_S)) {
                mVel.y -= 50.f;
                mState = PlayerState::Moving;
            }
            else if (p_Input->KeyHold(GLFW_KEY_D)) {
                mVel.x += 50.f;
                mState = PlayerState::Moving;
                if (p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x < 0)
                {
                    p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(-p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().y);
                }
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && mDashTimer <= 0.0f)
                {
                    mVel.x += 300.f;
                    mCooldownTimer = 0.5f;
                    mDashTimer = 5.0f;
                    mState = PlayerState::Dash;
                }
            }
            else if (p_Input->KeyHold(GLFW_KEY_A)) {
                mVel.x -= 50.f;
                mState = PlayerState::Moving;
                if (p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x > 0)
                {
                    p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(-p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().y);
                }
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && mDashTimer <= 0.0f)
                {
                    mVel.x -= 100.f;
                    mCooldownTimer = 0.5f;
                    mDashTimer = 5.0f;
                    mState = PlayerState::Dash;
                }
            }
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && mCooldownTimer <= 0.0f)
        {
            ++mAttackCounter;
            mCooldownTimer = 0.5f;
            mState = PlayerState::Attacking;
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_RIGHT) && mBlockTimer <= 0.0f)
        {
            mCooldownTimer = 0.5f;
            mBlockTimer = 5.0f;
            mState = PlayerState::Block;
        }

        if (mCooldownTimer <= 0.0f)
        {
            mState = PlayerState::Idle;
            mAttackCounter = 0;
        }

        UpdateState();
        UpdateAttack();
        UpdatePhysics(Frametime);
        Animate(mState);
	}

    /*!*************************************************************************
    End State for Player Controller
    ****************************************************************************/
    void PlayerController::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string PlayerController::GetScriptName()
    {
        return "PlayerController";
    }

    /*!*************************************************************************
    Function to update current player state
    ****************************************************************************/
    void PlayerController::UpdateState()
    {
        if (mDamageTimer > 0.0f)
        {
            mState = PlayerState::Damage;
        }
    }

    /*!*************************************************************************
    Update Physics for Player
    ****************************************************************************/
    void PlayerController::UpdatePhysics(float Frametime)
    {
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetScriptEntityID());

        pRigid.SetVel(mPhys.friction(pRigid.GetVel(), Frametime));
        pRigid.SetVel(mPhys.accelent(pRigid.GetVel(), mVel, Frametime));
        vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
        pRigid.SetNextPos(nextPos);
    }

    

    /*!*************************************************************************
    Animate Player base on Texture set during player state
    ****************************************************************************/
    void PlayerController::Animate(PlayerState state)
    {
        switch (state)
        {
        case PlayerState::Idle:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Idle");
            break;
        case PlayerState::Moving:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Running");
            break;
        case PlayerState::Attacking:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Attack");
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetDisplayTime();
            break;
        case PlayerState::Dash:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Dashing");
            break;
        case PlayerState::Block:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Blocking");
            break;
        case PlayerState::Damage:
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("Damage");
            break;
        }
    }

    void PlayerController::UpdateAttack()
    {
        auto pCol = p_ecs.GetComponent<Collider>(GetScriptEntityID()).GetCollisionArray();
        if (mState == PlayerState::Attacking)
        {
            (pCol + 1)->is_Alive = true;
        }
        else
        {
            (pCol + 1)->is_Alive = false;
        }
    }

    void PlayerController::SetState(PlayerState state)
    {
        mState = state;
    }
}
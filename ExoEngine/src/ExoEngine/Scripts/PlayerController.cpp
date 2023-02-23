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
    PlayerController::PlayerController() : mState{ PlayerState::Idle }, mAttackCounter{ 0 }, mCooldownTimer{ 0.0f }, mChargedAttackTimer{ 0.0f }, mDashTimer{0.0f}, mIsBlockTimer{2.0f},
        mBlockCoolDownTimer{ 0.0f }, mDamageTimer{ 0.0f }, mDashTime{ 0.0f }, mIsDamaged{ false }, mIsBlocking{ false }, mVel{ vec2D() } {};

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

        if ((mDamageTimer <= 0.0f && mIsDamaged == true) && (mDamageTimer <= 0.0f && mIsBlocking == true))
        {
            mIsDamaged = false;
            for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
            {
                if (p_ecs.GetComponent<NameTag>(i).GetNameTag() == "HPBar")
                {
                    p_ecs.GetComponent<Attributes>(i).GetHealth() -= 2;
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
                    mDashTimer = 3.0f;
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
                    mDashTimer = 3.0f;
                    mState = PlayerState::Dash;
                }
            }
            //p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].should_play = true;
        }

        if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && mCooldownTimer <= 0.0f)
        {
            ++mAttackCounter;
            mCooldownTimer = 0.5f;
            mState = PlayerState::Attacking;
        }

        //std::cout <<"BlockCoolDownTimer" << mBlockCoolDownTimer << std::endl;
        //std::cout << "Is blocking " << mIsBlockTimer << std::endl;
        //std::cout << "Mouse is held" << p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) << std::endl;
        //std::cout << "Mouse is released " << p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_RIGHT) << std::endl;

        //if ((p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) && (mBlockCoolDownTimer <= 0.0f))
        //{
        //    mIsBlockTimer -= Frametime;
        //    std::cout << "Blocking" << std::endl;
        //    mState = PlayerState::Block;
        //    mCooldownTimer = 0.5f;            

        //    if (p_Input->MouseIsReleased(GLFW_MOUSE_BUTTON_RIGHT))
        //    {
        //        mIsBlockTimer = 2.0f;
        //        mBlockCoolDownTimer = 5.0f;
        //    }
        //    //if (mIsBlockTimer <= 0.0f)
        //    //{
        //    //    mBlockCoolDownTimer = 5.0f;
        //    //    mIsBlockTimer = 2.0f;
        //    //}
        //}
        
        if (!mIsBlocking) 
        {
            if ((p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) && (mBlockCoolDownTimer <= 0.0f)) 
            {
                mIsBlocking = true;
            }
            else 
            {
                mBlockCoolDownTimer -= Frametime;
            }
        }
        else 
        {
            if (p_Input->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) 
            {
                mIsBlockTimer -= Frametime;
               // std::cout << "Blocking" << std::endl;
                mState = PlayerState::Block;
                mCooldownTimer = 0.5f;
                if (mIsBlockTimer <= 0) 
                {
                    mIsBlockTimer = 2.0f;
                    mBlockCoolDownTimer = 5.0f;
                    mIsBlocking = false;
                }
            }
            else 
            {
                mIsBlockTimer = 2.0f;
                mBlockCoolDownTimer = 5.0f;
                mIsBlocking = false;
            }
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
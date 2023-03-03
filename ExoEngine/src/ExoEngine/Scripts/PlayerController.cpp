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
        mBlockCoolDownTimer{ 0.0f }, mDamageTimer{ 0.0f }, mDashTime{ 0.0f }, mDashDurationTimer{ 0.0f }, mTakenDamage{ 0 }, mStunnedTimer{ 1.0f }, mStunCoolDown{ 0.0f }, mIsDamaged{ false },
        mIsBlocking{ false }, mIsDashing{ false }, mVel{ vec2D(0, 0) } {};

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
        std::cout << "Script initialized" << std::endl;
	}

    /*!*************************************************************************
    Update Loop of Player Controller Script
    ****************************************************************************/
	void PlayerController::Update(float Frametime)
	{
        //if (mState == PlayerState::Damage)
        //{
        //    std::cout << "Player State is Damage " << std::endl;
        //}
        //if (mState == PlayerState::Idle)
        //{
        //    std::cout << "Player State is Idle " << std::endl;
        //}

        mCooldownTimer -= Frametime;
        mDashTimer -= Frametime;
        mDashDurationTimer -= Frametime;
        mStunCoolDown -= Frametime;
        if (mStunCoolDown <= 0) {
            mStunCoolDown = 0;
        }
        mDamageTimer <= 0 ? mDamageTimer = 0 : mDamageTimer-=Frametime;
        if (mCooldownTimer <= 0.0f)
        {
            mState = PlayerState::Idle;
            mAttackCounter = 0;
        }
        mVel.x = 0.0f;
        mVel.y = 0.0f;

        std::cout << "is damaged: " << mIsDamaged << std::endl;
        std::cout << "damage timer: " << mDamageTimer << std::endl;
        std::cout << "stun timer: " << mStunCoolDown << std::endl;
        std::cout << "Entity: " << GetScriptEntityID() << std::endl;

        if (mStunCoolDown > 0) {
            mState = PlayerState::Damage;
            std::cout << "is stunned" << std::endl;
        }
        else {
            auto& mPlayerAttributes = p_ecs.GetComponent<Attributes>(GetScriptEntityID());
            if ((mDamageTimer <= 0.0f && mIsDamaged == true) && (mIsBlocking == false))
            {
                std::cout << "Taken Unshielded Damage" << std::endl;
                mDamageTimer = 2.5f;
                mIsDamaged = false;
                mPlayerAttributes.SetHealth(mPlayerAttributes.GetHealth() - mTakenDamage);
                if (mPlayerAttributes.GetHealth() <= 0)
                {
                    mPlayerAttributes.SetHealth(0);
                }
                mStunCoolDown = mStunnedTimer;
                mVel.x = 0.0f;
                mVel.y = 0.0f;
            }


            if ((mDamageTimer <= 0.0f && mIsDamaged == true) && (mIsBlocking == true))
            {
                std::cout << "Taken Shielded Damage" << std::endl;
                mDamageTimer = 2.5f;
                mIsDamaged = false;
                //auto& mPlayerAttributes = p_ecs.GetComponent<Attributes>(GetScriptEntityID());
                mPlayerAttributes.SetHealth(mPlayerAttributes.GetHealth() - (mTakenDamage / 5));
                if (mPlayerAttributes.GetHealth() <= 0)
                {
                    mPlayerAttributes.SetHealth(0);
                }
                mVel.x = 0.0f;
                mVel.y = 0.0f;
            }

            if ((p_Input->KeyHold(GLFW_KEY_W) || p_Input->KeyHold(GLFW_KEY_D)
                || p_Input->KeyHold(GLFW_KEY_S) || p_Input->KeyHold(GLFW_KEY_A)))
            {

                mCooldownTimer = 0.1f;
                if (p_Input->KeyHold(GLFW_KEY_W)) {
                    mVel.y = 1.0f;
                    mState = PlayerState::Moving;
                }
                else if (p_Input->KeyHold(GLFW_KEY_S)) {
                    mVel.y = -1.0f;
                    mState = PlayerState::Moving;
                }
                if (p_Input->KeyHold(GLFW_KEY_D)) {
                    mVel.x = 1.0f;
                    mState = PlayerState::Moving;
                    if (p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x < 0)
                    {
                        p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(-p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().y);
                    }
                    if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && mDashTimer <= 0.0f)
                    {
                        mIsDashing = true;
                        mDashTimer = 3.0f; //cd before player can dash again
                        mDashDurationTimer = 0.2f; //how long dash lasts
                        mCooldownTimer = 0.5f; // input delay timer
                        mState = PlayerState::Dash;
                    }

                    if (mIsDashing == true)
                    {
                        mState = PlayerState::Dash;
                        if (mDashDurationTimer <= 0.0f)
                        {
                            mIsDashing = false;
                        }
                    }
                }
                else if (p_Input->KeyHold(GLFW_KEY_A)) {
                    mVel.x = -1.0f;
                    mState = PlayerState::Moving;
                    if (p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x > 0)
                    {
                        p_ecs.GetComponent<Transform>(GetScriptEntityID()).SetScale(-p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().x, p_ecs.GetComponent<Transform>(GetScriptEntityID()).GetScale().y);
                    }
                    if (p_Input->isKeyPressed(GLFW_KEY_LEFT_SHIFT) && mDashTimer <= 0.0f)
                    {
                        mIsDashing = true;
                        mDashTimer = 3.0f; //cd before player can dash again
                        mDashDurationTimer = 0.2f; //how long dash lasts
                        mCooldownTimer = 0.5f; // input delay timer
                        mState = PlayerState::Dash;
                    }

                    if (mIsDashing == true)
                    {
                        mState = PlayerState::Dash;
                        if (mDashDurationTimer <= 0.0f)
                        {
                            mIsDashing = false;
                        }
                    }
                }
                //p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].should_play = true;
            }

            if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && mCooldownTimer <= 0.0f)
            {
                ++mAttackCounter;
                mCooldownTimer = 0.5f;
                mState = PlayerState::Attacking;
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
            else
            {
                p_ecs.GetComponent<Collider>(GetScriptEntityID())[1].is_Alive = false;
            }
            /*  if (mState == PlayerState::Attacking)
              {
                  p_ecs.GetComponent<Collider>(GetScriptEntityID())[1].is_Alive = true;
                  std::cout << "check" << std::endl;
              }
              else
                  p_ecs.GetComponent<Collider>(GetScriptEntityID())[1].is_Alive = false;*/
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

                  //Blocking
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
                    mIsBlockTimer -= Frametime; //Blocking duration
                    std::cout << "Blocking for " << mIsBlockTimer << std::endl;
                    mState = PlayerState::Block;
                    mCooldownTimer = 0.5f; // input delay timer
                    if (mIsBlockTimer <= 0)
                    {
                        mIsBlockTimer = 2.0f;
                        mBlockCoolDownTimer = 5.0f;
                        mIsBlocking = false;
                    }
                }
                else
                {
                    //if block ends early, update timers
                    mIsBlockTimer = 2.0f;
                    mBlockCoolDownTimer = 5.0f;
                    mIsBlocking = false;
                }
            }

        }
        

        //if (mIsDamaged && (mDamageTimer <= 0.0f))
        //{
        //    mState = PlayerState::Damage;
        //}


        //if (mPlayerAttributes.GetHealth() <= 0.0f)
        //{
        //    mState = PlayerState::Dead;
        //}

        //UpdateState();
        //UpdateAttack();
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
    
    void PlayerController::SetDamageTimer(float timer)
    {
        mDamageTimer = timer;
    }

    float& PlayerController::GetDamageTimer()
    {
        return mDamageTimer;
    }
}
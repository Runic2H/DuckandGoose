/*!*************************************************************************
****
\file PlayerController.h
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
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	/*!*************************************************************************
	Class for Player Controller Script
	****************************************************************************/
	class PlayerController : public IScript
	{
	public:
		/*!*************************************************************************
		enum class for player states
		****************************************************************************/
		enum class PlayerState
		{
			Idle,
			Moving,
			Attacking,
			Dash,
			Block,
			Stunned,
			Damage,
			Dead
		};
		/*!*************************************************************************
		Default constructor for Player Controller
		****************************************************************************/
		PlayerController();
		/*!*************************************************************************
		Default destructor for Player Controller
		****************************************************************************/
		~PlayerController() = default;
		/*!*************************************************************************
		Returns a new copy of PlayerController Script
		****************************************************************************/
		virtual PlayerController* Clone() const override;
		/*!*************************************************************************
		Start State of PlayerController Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update Loop of Player Controller Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for Player Controller
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override;

		/*!*************************************************************************
		Function to update current player state
		****************************************************************************/
		void UpdateState();

		/*!*************************************************************************
		Update Physics for Player
		****************************************************************************/
		void UpdatePhysics(float Frametime);

		/*!*************************************************************************
		Animate Player base on Texture set during player state
		****************************************************************************/
		void Animate(PlayerState state);

		void SetState(PlayerState state);

		void SetDamageTimer(float timer);
		float &GetDamageTimer();
		void SetDamageValue(int i) { mTakenDamage = i; }
		/*set damage timer to private
		create getter function
		retrieve damage timer by reference*/
		void UpdateAttack();

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		PlayerState mState, previousState;
		int mAttackCounter;
		float mCooldownTimer;
		float mChargedAttackTimer;
		float mDashTimer;
		float mDashDurationTimer;
		float mIsBlockTimer;
		float mBlockCoolDownTimer;
		vec2D mVel;
		entityPhysics mPhys;
		float mDamageTimer;
		int mTakenDamage;
		float mStunnedTimer;
		float mStunCoolDown;
	public:
		bool mIsDamaged;
		float mDashTime;
		bool mIsBlocking;
		bool mIsDashing;
	};
}
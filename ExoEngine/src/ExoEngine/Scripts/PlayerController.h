#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class PlayerController : public IScript
	{
	public:
		enum class PlayerState
		{
			Idle,
			Moving,
			Attacking,
			Dash,
			Block,
			Stunned
		};
		PlayerController();
		~PlayerController() = default;
		virtual PlayerController* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual std::string GetScriptName() override;

		void UpdateState();
		void UpdatePhysics(float Frametime);

		void Animate(PlayerState state);

	private:
		PlayerState mState;
		int mAttackCounter;
		float mCooldownTimer;
		float mChargedAttackTimer;
		float mDashTimer;
		float mBlockTimer;
		bool mIsBlocking;
		bool mIsAttacking;
		bool mIsStunned;
		bool mIsIdle;
		bool mIsMoving;
		bool mIsDashing;
		vec2D mVel;
		entityPhysics mPhys;
	};
}
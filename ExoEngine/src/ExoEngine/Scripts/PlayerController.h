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
			Block
		};
		PlayerController() = default;
		~PlayerController() = default;
		virtual PlayerController* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual std::string GetScriptName() override;

		void Animate(PlayerState state);
	private:
		PlayerState mState;
		int mAttackCounter{ 0 };
		float mCooldownTimer{ 0.0f };
		entityPhysics mPhys;
	};
}
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"
#include "Platform/Logic/StateMachines/StateMachine.h"
#include "Platform/Logic/States/IStates.h"
#include "Platform/Logic/States/OnIdle.h"
#include "Platform/Logic/States/OnMove.h"
#include "Platform/Logic/States/OnAttack.h"


namespace EM
{

	class PlayerControl : public IScript
	{
	public:
		PlayerControl() : mPlayerStateMachine(GetScriptEntityID()) {}
		~PlayerControl() = default;
		virtual IScript* Clone() const override
		{
			return new PlayerControl(*this);
		}
		virtual void Start() override
		{
			mPlayerStateMachine.ChangeState(new OnIdle());
		}
		virtual void Update(float Frametime) override
		{
			for (auto key : p_Input->mKeyStatus)
			{
				if (key.second == GLFW_PRESS) {
					mPlayerStateMachine.HandleInput(key.first);
				}
			}
			mPlayerStateMachine.OnUpdate(Frametime);
		}
		virtual void End() override
		{

		}

		virtual std::string GetScriptName() override
		{
			return "PlayerControl";
		}
	private:
		StateMachine mPlayerStateMachine;
	};
}
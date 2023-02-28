#pragma once
#include "empch.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/ECS/ECS.h"
#include "Platform/Logic/StateMachines/StateMachine.h"

namespace EM
{
	class StateMachine;

	class IStates
	{
	public:
		virtual ~IStates() = default;
		virtual IStates* HandleInput(StateMachine* stateMachine, const int& key) = 0;
		virtual void OnEnter(StateMachine* stateMachine) = 0;
		virtual void OnUpdate(StateMachine* stateMachine, float Frametime) = 0;
		virtual void OnExit(StateMachine* stateMachine) = 0;
	};

}
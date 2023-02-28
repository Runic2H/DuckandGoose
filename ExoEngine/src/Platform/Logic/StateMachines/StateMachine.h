#pragma once
#include "empch.h"
#include "ExoEngine/ECS/Types.h"

namespace EM
{
	class IStates;

	class StateMachine
	{
	public:
		StateMachine();
		StateMachine(Entity entity);

		~StateMachine() = default;

		//PlayerStates* GetCurrState();

		void ChangeState(IStates* pNewState);

		void HandleInput(const int& key);

		Entity& GetEntityID();

		void OnUpdate(float Frametime);

	private:
		IStates* mCurrState;
		Entity mEntityID;
	};
}
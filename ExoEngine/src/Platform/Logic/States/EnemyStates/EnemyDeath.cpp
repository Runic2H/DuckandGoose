#include "empch.h"
#include "EnemyDeath.h"
#include "ExoEngine/Scripts/GateController.h"

namespace EM
{
	EnemyDeath::EnemyDeath(StateMachine* stateMachine) : deathTime{ 5.0f } {}

	IStates* EnemyDeath::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}

	void EnemyDeath::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("MeleeDeath");
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Gate")
			{
				auto& logic = p_ecs.GetComponent<Logic>(i);
				dynamic_cast<GateController*>(logic.GetScriptByName("GateController"))->enemies -= 1;
			}
		}
	}
	void EnemyDeath::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		deathTime -= Frametime;
		if (deathTime <= 0) {
			p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Blank");
		}
	}
	void EnemyDeath::OnExit(StateMachine* stateMachine)
	{
		std::cout << "Death Animation Exit" << std::endl;
		delete this;
	}
}
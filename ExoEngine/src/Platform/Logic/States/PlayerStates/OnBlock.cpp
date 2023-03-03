#include "OnBlock.h"

namespace EM
{
	OnBlock::OnBlock(StateMachine* stateMachine) : stats{ p_ecs.GetComponent<PlayerAttributes>(stateMachine->GetEntityID()) } {}

	IStates* OnBlock::HandleInput(StateMachine* stateMachine, const int& key)
	{
		return nullptr;
	}
	void OnBlock::OnEnter(StateMachine* stateMachine)
	{
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).SetTexture("Block");
	}
	void OnBlock::OnUpdate(StateMachine* stateMachine, float Frametime)
	{
		std::cout << "Blocking" << std::endl;
		
	}
	void OnBlock::OnExit(StateMachine* stateMachine)
	{
		std::cout << "BlockingExit" << std::endl;
		p_ecs.GetComponent<Sprite>(stateMachine->GetEntityID()).GetIndex().x = 0;
		delete this;
	}
}
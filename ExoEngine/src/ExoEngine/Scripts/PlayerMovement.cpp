#include "PlayerMovement.h"

namespace EM
{
	PlayerMovement::PlayerMovement() {}
	PlayerMovement* PlayerMovement::Clone() const
	{
		 return new PlayerMovement(*this); 
	}
	void PlayerMovement::Start() {}

	void PlayerMovement::Update(float Frametime)
	{
		auto& transform = p_ecs.GetComponent<Transform>(GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetEntityID());

		if (p_Input->isKeyPressed(GLFW_KEY_UP))
		{
			transform.GetPos().y += rigidbody.GetVel().y * Frametime;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_DOWN))
		{
			transform.GetPos().y -= rigidbody.GetVel().y * Frametime;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_LEFT))
		{
			transform.GetPos().x -= rigidbody.GetVel().x * Frametime;
		}
		if (p_Input->isKeyPressed(GLFW_KEY_RIGHT))
		{
			transform.GetPos().x += rigidbody.GetVel().x * Frametime;
		}
	}
	void PlayerMovement::End()
	{

	}
}
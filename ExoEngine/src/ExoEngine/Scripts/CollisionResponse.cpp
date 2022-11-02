#include "CollisionResponse.h"

namespace EM
{
	CollisionResponse::CollisionResponse() {}
	CollisionResponse* CollisionResponse::Clone() const
	{
		 return new CollisionResponse(*this); 
	}
	void CollisionResponse::Start() {}

	void CollisionResponse::Update(float Frametime)
	{
        auto& transform = p_ecs.GetComponent<Transform>(GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetEntityID());
		auto& col = p_ecs.GetComponent<Collider>(GetEntityID());
		if (col.GetHit()) {
			std::cout << "Current velocity: " << rigidbody.GetVel().x << ", " << rigidbody.GetVel().y << "\n";
			vec2D inverse = rigidbody.GetDir(); 
			inverse.x *= -25;
			inverse.y *= -25;
			rigidbody.SetVel(mPhys.accelent(inverse, rigidbody.GetVel(), Frametime));
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			std::cout << "Adjusted velocity: " << rigidbody.GetVel().x << ", " << rigidbody.GetVel().y << "\n";
			rigidbody.SetNextPos(nextPos);
		}
	}
	void CollisionResponse::End()
	{

	}
}
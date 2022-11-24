#include "CollisionResponse.h"

namespace EM
{
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
			//std::cout << "Current velocity: " << rigidbody.GetVel().x << ", " << rigidbody.GetVel().y << "\n";
			vec2D response = rigidbody.GetVel(); 
			vec2D normal = col.GetNormal();
			float dotProd = dotProduct(normal, response);
			if (dotProd <= 0) {
				normal = normal * dotProd;
				response -= normal;
				rigidbody.SetVel(response);
			}
			vec2D nextPos = transform.GetPos() + rigidbody.GetVel();
			rigidbody.SetNextPos(nextPos);
		}
	}
	void CollisionResponse::End()
	{
		delete this;
	}

	std::string CollisionResponse::GetScriptName() { return "CollisionResponse"; }
}
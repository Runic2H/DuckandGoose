#include "EnemyMovement.h"

namespace EM
{
	EnemyMovement::EnemyMovement() {}
	EnemyMovement* EnemyMovement::Clone() const
	{
		return new EnemyMovement(*this);
	}
	void EnemyMovement::Start() {}

	void EnemyMovement::Update(float Frametime)
	{
		auto& transform = p_ecs.GetComponent<Transform>(GetEntityID());
		auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetEntityID());
		for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
		{
			if (p_ecs.HaveComponent<Player>(i))
			{
				rigidbody.SetDir(p_ecs.GetComponent<Transform>(i).GetPos().x - transform.GetPos().x, p_ecs.GetComponent<Transform>(i).GetPos().y - transform.GetPos().y);
			}
		}
		if (dotProduct(transform.GetPos(), rigidbody.GetDir()) < 5.0f)
		{
			transform.GetPos() += (rigidbody.GetDir() * rigidbody.GetFriction() * Frametime);
		}
	}

	void EnemyMovement::End() {}
}
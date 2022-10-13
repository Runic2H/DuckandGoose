#pragma once
#include "RigidBody.h"
#include "physics.h"
#include "transformation.h"
//#include "../ECS/ECS.h"
#include "ExoEngine/ECS/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
	class PhysicsSystem : System
	{
		void Init();

		void Update(float dt);
	};

}

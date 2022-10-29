#pragma once

#include "ECS.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "Platform/System/SystemManager.h"
#include "Types.h"
#include "empch.h"
#include "Serialization/JSONserialization.h"
#include "Serialization/JSONincludes.h"

namespace EM
{
	extern ECS ecs;

	class SceneManager : public JSONSerializer
	{
	public:
		void OnInit()
		{
			ecs.RegisterComponent<Transform>();
			ecs.RegisterComponent<RigidBody>();
			ecs.RegisterComponent<Sprite>();
		}

		Entity GetEntities()
		{
			return ecs.GetTotalEntities();
		}

		virtual bool Deserialize(const rapidjson::Value& obj);

		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

	};
}
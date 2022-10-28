#pragma once
#include "Serialization/JSONserialization.h"
#include "empch.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/ECS/Types.h"

namespace EM
{
	class IComponent : public JSONSerializer
	{
	public:
		virtual ~IComponent() = default;
		virtual void ToEditor() {}
		virtual bool Deserialize(const rapidjson::Value& obj) = 0;
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const = 0;
		virtual std::string GetComponentName() = 0;
	};
}
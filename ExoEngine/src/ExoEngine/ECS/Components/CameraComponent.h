#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"

namespace EM {

	class CameraComponent : public IComponent
	{
	public:
		CameraComponent();
		~CameraComponent() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
	private:
	};
}

#include "empch.h"
#include "CameraComponent.h"

namespace EM {
	CameraComponent::CameraComponent()
	{
	}
	bool CameraComponent::Deserialize(const rapidjson::Value& obj)
	{
		return false;
	}
	bool CameraComponent::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		return false;
	}
}
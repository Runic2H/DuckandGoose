#include "Transform.h"

namespace EM
{
	//Transform
	Transform::Transform() : position{ vec2D(1.0f,1.0f) }, scale{ vec2D(1.0f,1.0f) }, rot{ 0.0f } {}

	bool Transform::Deserialize(const rapidjson::Value& obj)
	{
		position = vec2D(obj["posX"].GetFloat(), obj["posY"].GetFloat());
		scale = vec2D(obj["scaleX"].GetFloat(), obj["scaleY"].GetFloat());
		rot = obj["Rot"].GetFloat();
		return true;
	}
	bool Transform::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("posX");
		writer->Double(position.x);
		writer->Key("posY");
		writer->Double(position.y);
		writer->Key("scaleX");
		writer->Double(scale.x);
		writer->Key("scaleY");
		writer->Double(scale.y);
		writer->Key("Rot");
		writer->Double(rot);
		writer->EndObject();
		return true;
	}

	std::string Transform::GetComponentName()
	{
		std::string className = __FUNCTION__;
		size_t found = className.find_last_of("::") - 1;
		className = className.substr(0, found);
		found = className.find_last_of("::") + 1;
		className = className.substr(found);
		return className;
	}
	//End Transform
}
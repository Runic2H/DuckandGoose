#include "RigidBody.h"

namespace EM
{
	//RigidBody
	RigidBody::RigidBody() : min{ vec2D() }, max{ vec2D() }, vel{ vec2D() }, initvel{ vec2D() }, nextpos{ vec2D() }, collider{ Col_Type::none } {}

	bool RigidBody::Deserialize(const rapidjson::Value& obj)
	{
		min = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		max = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		vel = vec2D(obj["velX"].GetFloat(), obj["velY"].GetFloat());
		initvel = vec2D(obj["initX"].GetFloat(), obj["initY"].GetFloat());
		if (obj["col"].GetInt() == 0) {
			collider = Col_Type::none;
		}
		else if (obj["col"].GetInt() == 1) {
			collider = Col_Type::circle;
		}
		else if (obj["col"].GetInt() == 2) {
			collider = Col_Type::line;
		}
		else if (obj["col"].GetInt() == 3) {
			collider = Col_Type::rect;
		}
		return true;
	}
	bool RigidBody::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("minX");
		writer->Double(min.x);
		writer->Key("minY");
		writer->Double(min.y);
		writer->Key("maxX");
		writer->Double(max.x);
		writer->Key("maxY");
		writer->Double(max.y);
		writer->Key("velX");
		writer->Double(vel.x);
		writer->Key("velY");
		writer->Double(vel.y);
		writer->Key("initX");
		writer->Double(initvel.x);
		writer->Key("initY");
		writer->Double(initvel.y);
		writer->Key("col");//------------------------------
		if (collider == Col_Type::none) {
			writer->Int(0); //-----Collider serialization
		}
		else if (collider == Col_Type::circle) {
			writer->Int(1);
		}
		else if (collider == Col_Type::line) {
			writer->Int(2);
		}
		else if (collider == Col_Type::rect) {
			writer->Int(3);
		}
		writer->EndObject();
		return true;
	}

	std::string RigidBody::GetComponentName()
	{
		std::string className = __FUNCTION__;
		size_t found = className.find_last_of("::") - 1;
		className = className.substr(0, found);
		found = className.find_last_of("::") + 1;
		className = className.substr(found);
		return className;
	}
	//End RigidBody
}
/*!*************************************************************************
****
\file Components.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains all the Various Components to be used in the ECS
in the future. Currently, Every Component is still handling its own data
by inheriting from an abstract class of the JSONSerializer to serialize and
deserialize its data

****************************************************************************
***/

#include "Components.h"

namespace EM
{
	//RigidBody
	RigidBody::RigidBody() : min{ vec2D() }, max{ vec2D() }, vel{ vec2D() }, initvel{ vec2D() }, nextpos{vec2D()}, collider{ Col_Type::none }
	{
		//RigidBody::SerializeToFile("RigidBody.json");
	};
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

	//Transform
	Transform::Transform() : position{ vec2D(1.0f,1.0f) }, scale{ vec2D(1.0f,1.0f) }, rot {0.0f} {}

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

	//Window
	WinData::WinData() : title{"Exomata"} , width {0}, height(0), currentWidth{0}, currentHeight{0}
	{
		//WinData::SerializeToFile("Window.json");
	};
	bool WinData::Deserialize(const rapidjson::Value& obj)
	{
		title = obj["Title"].GetString();
		width = obj["Width"].GetUint();
		height = obj["Height"].GetUint();
		currentWidth = obj["Cwidth"].GetUint();
		currentHeight = obj["Cheight"].GetUint();
		return true;
	}
	bool WinData::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
			writer->Key("Title");
			writer->String(title.c_str());
			writer->Key("Width");
			writer->Uint(width);
			writer->Key("Height");
			writer->Uint(height);
			writer->Key("Cwidth");
			writer->Uint(currentWidth);
			writer->Key("Cheight");
			writer->Uint(currentHeight);
		writer->EndObject();
		return true;
	}

	std::string WinData::GetComponentName()
	{
		std::string className = __FUNCTION__;
		size_t found = className.find_last_of("::") - 1;
		className = className.substr(0, found);
		found = className.find_last_of("::") + 1;
		className = className.substr(found);
		return className;
	}
}
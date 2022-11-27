/*!*************************************************************************
****
\file Player.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Player Component used for scripting purposes, such as tagging the
camera to the player component or enemy pathfinding

****************************************************************************
***/
#include "empch.h"
#include "Tag.h"

namespace EM
{
	Tag::Tag() : mTag{"Untagged"}, mTargetTag{""} {}

	bool Tag::Deserialize(const rapidjson::Value& obj)
	{
		mTag = obj["Tag"].GetString();
		mTargetTag = obj["TargetTag"].GetString();
		return true;
	}

	bool Tag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Tag");
		writer->String(mTag.c_str());
		writer->Key("TargetTag");
		writer->String(mTargetTag.c_str());
		writer->EndObject();
		return true;
	}
}
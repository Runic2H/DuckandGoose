/*!*************************************************************************
****
\file NameTag.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400 / GAM200
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  NameTag Component for tagging each entity with a string name

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "NameTag.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for NameTag
	****************************************************************************/
	NameTag::NameTag() : mName{"none"} {}

	/*!*************************************************************************
	Deserialize NameTag Component
	****************************************************************************/
	bool NameTag::Deserialize(const rapidjson::Value& obj)
	{
		mName = obj["NameTag"].GetString();
		return true;
	}

	/*!*************************************************************************
	Serialize NameTag Component
	****************************************************************************/
	bool NameTag::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->Key("NameTag");
		writer->String(mName.c_str());
		return true;
	}
}
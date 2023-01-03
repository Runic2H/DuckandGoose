/*!*****************************************************************************
\file Collider.h
\author Elton Teo Zhe Wei, Tan Ek Hern
\par DP email: e.teo@digipen.edu, t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 30-10-2022
\brief  This file contains function definitions for some of the collider
		component's member functions
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "Collider.h"

namespace EM
{
	/*!*************************************************************************
	This is the constructor for the collider component to initialize all data members
	Data members will be changed during the de-serialization function call if the
	specific entity has serialized collider information
	****************************************************************************/
	Collider::Collider() {}
	/*!*************************************************************************
	This function de-serializes the level colliders from the given level json file
	****************************************************************************/
	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		for (auto i = obj["ColliderType"].GetArray().Begin(); i != obj["ColliderType"].GetArray().End(); ++i)
		{
			mCol.push_back(static_cast<ColliderType>(i->GetInt()))
		}
		for (auto i = obj["min"].GetArray().Begin(); i != obj["min"].GetArray().End(); ++i)
		{
			vec2D in = vec2D(i->GetFloat(), 0);
			++i;
			in.y = i->GetFloat();
			mMin.push_back(in);
		}
		for (auto i = obj["max"].GetArray().Begin(); i != obj["max"].GetArray().End(); ++i)
		{
			vec2D in = vec2D(i->GetFloat(), 0);
			++i;
			in.y = i->GetFloat();
			mMax.push_back(in);
		}
		for (auto i = obj["offset"].GetArray().Begin(); i != obj["offset"].GetArray().End(); ++i)
		{
			vec2D in = vec2D(i->GetFloat(), 0);
			++i;
			in.y = i->GetFloat();
			mOffset.push_back(in);
		}
		for (auto i = obj["radius"].GetArray().Begin(); i != obj["radius"].GetArray().End(); ++i)
		{
			 mRadius.push_back(i->GetFloat());
		}
		return true;
	}
	/*!*************************************************************************
	This function saves the level information by serializing it to the level json 
	file
	****************************************************************************/
	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ColliderType");
		writer->StartArray();
		for (size_t i = 0; i < mCol.size(); ++i)
		{
			writer->Int(static_cast<int>(mCol[i]));
		}
		writer->EndArray();
		writer->Key("min");
		writer->StartArray();
		for (size_t i = 0; i < mMin.size(); ++i)
		{
			writer->Double(mMin[i].x);
			writer->Double(mMin[i].y);
		}
		writer->EndArray();
		writer->Key("max");
		writer->StartArray();
		for (size_t i = 0; i < mMax.size(); ++i)
		{
			writer->Double(mMax[i].x);
			writer->Double(mMax[i].y);
		}
		writer->EndArray();
		writer->Key("offset");
		writer->StartArray();
		for (size_t i = 0; i < mOffset.size(); ++i)
		{
			writer->Double(mOffset[i].x);
			writer->Double(mOffset[i].y);
		}
		writer->EndArray();
		writer->Key("radius");
		writer->StartArray();
		for (size_t i = 0; i < mRadius.size(); ++i)
		{
			writer->Double(mRadius[i]);
		}
		writer->EndArray();
		writer->EndObject();
		return true;
	}
}
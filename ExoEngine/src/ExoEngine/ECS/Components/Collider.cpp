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
	Collider::Collider() {
		for (int i = 0; i < 2; ++i)
		{
			mColArr[i].mCol = ColliderType::none;
			mColArr[i].mCollisionNormal = vec2D();
			mColArr[i].mMin = vec2D();
			mColArr[i].mMax = vec2D();
			mColArr[i].mOffset = vec2D();
			mColArr[i].mHit = 0;
			mColArr[i].mRadius = 0;
			mColArr[i].is_Alive = true;
		}
	}
	/*!*************************************************************************
	This function de-serializes the level colliders from the given level json file
	****************************************************************************/
	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		for (int i = 0; i < 2; ++i)
		{
			mColArr[i].mCol = static_cast<ColliderType>(obj["Collider"][i]["ColliderType"].GetInt());
			mColArr[i].mMin = vec2D(obj["Collider"][i]["minX"].GetFloat(), obj["Collider"][i]["minY"].GetFloat());
			mColArr[i].mMax = vec2D(obj["Collider"][i]["maxX"].GetFloat(), obj["Collider"][i]["maxY"].GetFloat());
			mColArr[i].mOffset = vec2D(obj["Collider"][i]["offsetX"].GetFloat(), obj["Collider"][i]["offsetY"].GetFloat());
			mColArr[i].mRadius = obj["Collider"][i]["radius"].GetFloat();
		}

		/*mColArr[1].mCol = static_cast<ColliderType>(obj["ColliderType"].GetInt());
		mColArr[1].mMin = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		mColArr[1].mMax = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		mColArr[1].mOffset = vec2D(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat());
		mColArr[1].mRadius = obj["radius"].GetFloat();*/

		return true;
	}
	/*!*************************************************************************
	This function saves the level information by serializing it to the level json 
	file
	****************************************************************************/
	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Collider");
		writer->StartArray();
		for (int i = 0; i < 2; ++i)
		{
			writer->StartObject();
			writer->Key("ColliderType");
			writer->Int(static_cast<int>(mColArr[i].mCol));
			writer->Key("minX");
			writer->Double(mColArr[i].mMin.x);
			writer->Key("minY");
			writer->Double(mColArr[i].mMin.y);
			writer->Key("maxX");
			writer->Double(mColArr[i].mMax.x);
			writer->Key("maxY");
			writer->Double(mColArr[i].mMax.y);
			writer->Key("offsetX");
			writer->Double(mColArr[i].mOffset.x);
			writer->Key("offsetY");
			writer->Double(mColArr[i].mOffset.y);
			writer->Key("radius");
			writer->Double(mColArr[i].mRadius);
			writer->EndObject();
		}
		writer->EndArray();
		writer->EndObject();
		
		//writer->Key("ColliderType");
		//writer->Int(static_cast<int>(mColArr[1].mCol));
		//writer->Key("minX");
		//writer->Double(mColArr[1].mMin.x);
		//writer->Key("minY");
		//writer->Double(mColArr[1].mMin.y);
		//writer->Key("maxX");
		//writer->Double(mColArr[1].mMax.x);
		//writer->Key("maxY");
		//writer->Double(mColArr[1].mMax.y);
		//writer->Key("offsetX");
		//writer->Double(mColArr[1].mOffset.x);
		//writer->Key("offsetY");
		//writer->Double(mColArr[1].mOffset.y);
		//writer->Key("radius");
		//writer->Double(mColArr[1].mRadius);
		//writer->EndObject();
		return true;
	}
}
/*!*************************************************************************
****
\file Logic.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Logic Component for all the scripts being used by each entity.
Contains a vector for scripts which is looped and calls each scripts update
function

****************************************************************************
***/

#include "Logic.h"
#include "ExoEngine/Scripts/PlayerMovement.h"
#include "ExoEngine/Scripts/EnemyMovement.h"
#include "ExoEngine/Scripts/CollisionResponse.h"

namespace EM
{
	Logic::Logic()
	{
	}

	Logic::Logic(const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetEntityID(this->entityID);
		}
	}

	Logic& Logic::operator= (const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetEntityID(this->entityID);
		}
		return *this;
	}

	//Sets the Script's entity to retrieve data only from that entity
	void Logic::SetScriptEntity(Entity entity)
	{
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->SetEntityID(entity);
		}
	}

	bool Logic::Deserialize(const rapidjson::Value& obj)
	{
		for (auto i = obj["ScriptName"].GetArray().Begin(); i != obj["ScriptName"].GetArray().End(); ++i)
		{
			mScriptNameVector.push_back(i->GetString());
		}
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			if (mScriptNameVector[i] == "PlayerMovement")
			{
				mScriptsVector.push_back(new PlayerMovement());
			}
			if (mScriptNameVector[i] == "EnemyMovement")
			{
				mScriptsVector.push_back(new EnemyMovement());
			}
			if (mScriptNameVector[i] == "CollisionResponse")
			{
				mScriptsVector.push_back(new CollisionResponse());
			}
		}
		return true;
	}

	bool Logic::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ScriptName");
		writer->StartArray();
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			writer->String(mScriptNameVector[i].c_str());
		}
		writer->EndArray();
		writer->EndObject();
		return true;
	}

	//Inserts the scripts into the vector to loop through
	void Logic::InsertScript(IScript* script, Entity entity)
	{
		mScriptNameVector.push_back(script->GetScriptName());
		mScriptsVector.push_back(script);
		entityID = entity;
	}
}
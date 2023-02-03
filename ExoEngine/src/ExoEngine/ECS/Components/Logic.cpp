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

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Logic.h"
#include "ExoEngine/Scripts/EnemyMovement.h"
#include "ExoEngine/Scripts/CollisionResponse.h"
#include "ExoEngine/Scripts/ButtonResponse.h"
#include "ExoEngine/Scripts/PlayerController.h"
#include "ExoEngine/Scripts/ScenerioScript.h"
#include "ExoEngine/Scripts/AudioManager.h"
#include "ExoEngine/Scripts/HUDController.h"

namespace EM
{
	/*!*************************************************************************
	Ctor for Logic Component
	****************************************************************************/
	Logic::Logic() { }

	/*!*************************************************************************
	Copy Ctor
	****************************************************************************/
	Logic::Logic(const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetScriptEntityID(this->entityID);
		}
	}
	/*!*************************************************************************
	Copy Assignment for operator overload
	****************************************************************************/
	Logic& Logic::operator= (const Logic& rhs)
	{
		mScriptNameVector = rhs.mScriptNameVector;
		mScriptsVector.resize(rhs.mScriptsVector.size());
		for (size_t i = 0; i < mScriptsVector.size(); ++i)
		{
			mScriptsVector[i] = rhs.mScriptsVector[i]->Clone();
			mScriptsVector[i]->SetScriptEntityID(this->entityID);
		}
		return *this;
	}

	/*!*************************************************************************
	Sets the Script's entity to retrieve data only from that entity
	****************************************************************************/
	void Logic::SetScriptEntity(Entity entity)
	{
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->SetScriptEntityID(entity);
		}
	}

	/*!*************************************************************************
	Deserialize for Logic Component
	****************************************************************************/
	bool Logic::Deserialize(const rapidjson::Value& obj)
	{
		/*if (!obj["ScriptName"].GetArray().Empty())
		{
			for (auto i = obj["ScriptName" + 1].GetArray().Begin(); i != obj["ScriptName"].GetArray().End(); ++i)
			{
				mScriptNameVector.push_back(i->GetString());
			}
			for (size_t i = 0; i < mScriptNameVector.size(); ++i)
			{
				if (mScriptNameVector[i] == "PlayerController")
				{
					mScriptsVector.push_back(new PlayerController());
				}
				if (mScriptNameVector[i] == "EnemyMovement")
				{
					mScriptsVector.push_back(new EnemyMovement());
				}
				if (mScriptNameVector[i] == "CollisionResponse")
				{
					mScriptsVector.push_back(new CollisionResponse());
				}
				if (mScriptNameVector[i] == "ButtonResponse")
				{
					mScriptsVector.push_back(new ButtonResponse());
				}
				if (mScriptNameVector[i] == "ScenerioScript")
				{
					mScriptsVector.push_back(new ScenerioScript());
				}
			}
		}*/

		for (int i = 0; i < obj["ScriptCount"].GetInt(); ++i)
		{
			mScriptNameVector.push_back(obj[std::to_string(i).c_str()].GetString());
				if (mScriptNameVector[i] == "PlayerController")
				{
					mScriptsVector.push_back(new PlayerController());
				}
				if (mScriptNameVector[i] == "EnemyMovement")
				{
					mScriptsVector.push_back(new EnemyMovement());
				}
				if (mScriptNameVector[i] == "CollisionResponse")
				{
					mScriptsVector.push_back(new CollisionResponse());
				}
				if (mScriptNameVector[i] == "ButtonResponse")
				{
					mScriptsVector.push_back(new ButtonResponse());
				}
				if (mScriptNameVector[i] == "ScenerioScript")
				{
					mScriptsVector.push_back(new ScenerioScript());
				}
				if (mScriptNameVector[i] == "AudioManager")
				{
					mScriptsVector.push_back(new AudioManager());
				}
				if (mScriptNameVector[i] == "HUDController")
				{
					mScriptsVector.push_back(new HUDController());
				}
		}

		return true;
	}

	/*!*************************************************************************
	Serialize for Logic Component
	****************************************************************************/
	bool Logic::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		int i = 0;
		writer->StartObject();
		//writer->StartArray();
		for (i = 0; i < mScriptNameVector.size(); ++i)
		{
			writer->Key(std::to_string(i).c_str());
			writer->String(mScriptNameVector[i].c_str());
		}
		//writer->EndArray();
		writer->Key("ScriptCount");
		writer->Int(i);
		writer->EndObject();
		return true;
	}

	//int Logic::FindScript( const std::string& scriptname)
	//{
	//	for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); i++)// pointer to the iscript
	//	{
	//		if()
	//	}
	//}

	/*!*************************************************************************
	Inserts the scripts into the vector to loop through
	****************************************************************************/
	void Logic::InsertScript(IScript* script, Entity entity)
	{
		mScriptNameVector.push_back(script->GetScriptName());
		mScriptsVector.push_back(script);
		script->SetScriptEntityID(entity);
	}

	void Logic::DeleteScript(std::string scriptname)
	{
		for (int idx = 0;idx < mScriptNameVector.size(); idx++) {
			if (mScriptNameVector[idx] == scriptname) {
				mScriptNameVector.erase(mScriptNameVector.begin() + idx);
				mScriptsVector.erase(mScriptsVector.begin() + idx);
				std::cout << "Deleted Script: " << scriptname << "\n";
			}
		}
	}

	/*!*************************************************************************
	Clear all Scripts inside the Vector
	****************************************************************************/
	void Logic::ClearAllScripts()
	{
		mScriptNameVector.clear();
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->End();
		}
	}

	IScript* Logic::GetScriptByName(std::string ScriptName)
	{
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			if (mScriptNameVector[i] == ScriptName)
			{
				return mScriptsVector[i];
			}
		}
		return nullptr;
	}
}
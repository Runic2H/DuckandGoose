#include "Logic.h"
#include "ExoEngine/Scripts/PlayerMovement.h"
#include "ExoEngine/Scripts/EnemyMovement.h"

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

	void Logic::SetScriptEntity(Entity entity)
	{
		for (auto i = mScriptsVector.begin(); i != mScriptsVector.end(); ++i)
		{
			(*i)->SetEntityID(entity);
		}
	}

	bool Logic::Deserialize(const rapidjson::Value& obj)
	{
		mScriptNameVector.push_back(obj["ScriptName"].GetString());
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
		}
		return true;
	}

	bool Logic::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ScriptName");
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			writer->String(mScriptNameVector[i].c_str());
		}
		writer->EndObject();
		return true;
	}

	void Logic::InsertScript(IScript* script, Entity entity)
	{

		mScriptNameVector.push_back(script->GetScriptName());
		mScriptsVector.push_back(script);
		entityID = entity;
	}
}
#include "Logic.h"

namespace EM
{
	Logic::Logic() 
	{
		for (size_t i = 0; i < mScriptNameVector.size(); ++i)
		{
			
		}
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

	void Logic::InsertScript(std::string name, IScript* script)
	{
		mScriptNameVector.push_back(name);
		mScriptsVector.push_back(script);
	}
}
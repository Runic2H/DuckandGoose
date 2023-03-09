#include "empch.h"
#include "Attributes.h"

namespace EM
{
	Attributes::Attributes() : mHealth(75), mMaxHealth(100), mDamage(10), mChestHealth(50) {};

	bool Attributes::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		mMaxHealth = obj["Max Health"].GetInt();
		mDamage = obj["Damage"].GetInt();
		mChestHealth = obj["Chest Health"].GetInt();
		return true;
	}

	bool Attributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->Key("Max Health");
		writer->Int(mMaxHealth);
		writer->Key("Damage");
		writer->Int(mDamage);
		writer->Key("Chest Health");
		writer->Int(mChestHealth);
		//writer->EndObject();
		return true;
	}
}
#include "empch.h"
#include "Attributes.h"

namespace EM
{
	Attributes::Attributes() : mFiringCoolDown{ 2.0f }, mFireDurationTimer{ 1.0f }, mChargeCoolDown{ 2.0f }, mHazardDmg{ 20 }, mHazardType{HazardTypes::HAZARD_EMPTY} {}

	bool Attributes::Deserialize(const rapidjson::Value& obj)
	{
		mFiringCoolDown = obj["FiringCooldown"].GetFloat();
		mFireDurationTimer = obj["FiringDuration"].GetFloat();
		mChargeCoolDown = obj["ChargeDuration"].GetFloat();
		mHazardDmg = obj["HazardDamage"].GetInt();
		mHazardType = static_cast<Attributes::HazardTypes>(obj["HazardType"].GetInt());
		return true;
	}

	bool Attributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		//writer->StartObject();
		writer->Key("FiringCooldown");
		writer->Double(mFiringCoolDown);
		writer->Key("FiringDuration");
		writer->Double(mFireDurationTimer);
		writer->Key("ChargeDuration");
		writer->Double(mChargeCoolDown);
		writer->Key("HazardDamage");
		writer->Int(mHazardDmg);
		writer->Key("HazardType");
		writer->Int(static_cast<int>(mHazardType));
		//writer->EndObject();
		return true;
	}
}
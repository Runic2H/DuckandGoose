#include "empch.h"
#include "PlayerAttributes.h"

namespace EM
{
	PlayerAttributes::PlayerAttributes() : mHealth{ 100 }, mMaxHealth{ 100 }, mDamage{ 20 }, mAttackCounter{ 0 }, mDamageTimer{ 0 }, mDashTime{ 0 },
		mDashDurationTimer{0}, mIsBlockTimer{0}, mBlockCoolDownTimer{0}, mIsDamaged{false},
		mIsBlocking{ false }, mIsDashing{ false }, mVel{ vec2D(0,0) }, mDir{ vec2D(1,0) } {}

	bool PlayerAttributes::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		mMaxHealth = obj["Max Health"].GetInt();
		mDamage = obj["Damage"].GetInt();
		return true;
	}

	bool PlayerAttributes::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->Key("Max Health");
		writer->Int(mMaxHealth);
		writer->Key("Damage");
		writer->Int(mDamage);
		writer->EndObject();
		return true;
	}
}
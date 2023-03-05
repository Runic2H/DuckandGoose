#include "empch.h"
#include "PlayerAttributes.h"

namespace EM
{
	PlayerAttributes::PlayerAttributes() : mHealth{ 100 }, mMaxHealth{ 100 }, mDamage{ 20 }, mAttackCounter{ 0 }, mDamageCoolDown{ 0.0f }, mDashCoolDown{ 0.0f },
		mDashDurationTimer{ 0.0f }, mBlockCoolDown{ 2.0f }, mBlockDurationTimer{ 0.0f }, mCooldownTimer{ 0.0f }, mDamageTaken{ 0.0f }, mDamageDurationTimer{ 0.5f }, mIsDamaged{ false },
		mIsBlocking{ false }, mIsDashing{ false }, mVel{ vec2D(1.0f,1.0f) }, mDir{ vec2D(1.0f,0.0f) } {}

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
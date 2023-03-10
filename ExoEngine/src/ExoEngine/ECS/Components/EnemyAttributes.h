#pragma once
#include "IComponent.h"
#include "empch.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyAttributes : public IComponent
	{
	public:

		enum class EnemyTypes
		{
			ENEMY_NONE,
			ENEMY_MELEE,
			ENEMY_RANGED,
			ENEMY_SPECIAL,
			ENEMY_BOSS
		};

		EnemyAttributes();
		~EnemyAttributes() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	public:
		int mHealth;
		int mMaxHealth;
		int mDamage;
		float mAttackTimer;
		float mAttackCoolDown;
		float mDamageCoolDownTimer;
		float mDamageDurationTimer;
		bool mIsAlive;
		bool mIsDamaged;
		EnemyTypes mEnemyType;
		vec2D mVel;
		entityPhysics mPhys;
	};
}
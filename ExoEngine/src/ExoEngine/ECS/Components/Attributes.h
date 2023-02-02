#pragma once
#include "empch.h"
#include "IComponent.h"

namespace EM
{
	class Attributes : public IComponent
	{
	public:
		Attributes();
		~Attributes() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void SetHealth(int value) { mHealth = value; }

		void SetDamage(int value) { mDamage = value; }

		int& GetHealth() { return mHealth; }

		int& GetDamage() { return mDamage; }

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

	private:
		int mHealth;
		int mDamage;
	};
}
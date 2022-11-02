/*!*************************************************************************
****
\file Player.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  Player Component used for scripting purposes, such as tagging the
camera to the player component or enemy pathfinding

****************************************************************************
***/

#pragma once
#include "IComponent.h"

namespace EM
{
	class Player : public IComponent
	{
	public:
		Player();
		~Player() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void SetHealth(int health) { mHealth = health; }
		int& GetHealth() { return mHealth; }

	private:
		int mHealth;
	};
}
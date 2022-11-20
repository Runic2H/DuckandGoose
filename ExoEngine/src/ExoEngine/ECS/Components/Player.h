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
		void SetGod(bool tog) { ccGodMode = tog; }
		bool GetGod() { return ccGodMode; }
		void SetNoclip(bool tog) { ccNoclip = tog; }
		bool GetNoclip() { return ccNoclip; }
		void SetInfHP(bool tog) { ccInfHP = tog; }
		bool GetInfHP() { return ccInfHP; }
		void SetBerserk(bool tog) { ccBerserk = tog; }
		bool GetBerserk() { return ccBerserk; }
		void SetNoChill(bool tog) { ccNoChill = tog; }
		bool GetNoChill() { return ccNoChill; }
		void SetSanic(bool tog) { ccSanic = tog; }
		bool GetSanic() { return ccSanic; }

	private:
		int mHealth;
		bool ccGodMode; //all cheats on
		bool ccNoclip; //No collision with anything
		bool ccInfHP; //Infinite HP
		bool ccBerserk; //Extra damage
		bool ccNoChill; //No skill cooldowns
		bool ccSanic; //Go very fastk
	};
}
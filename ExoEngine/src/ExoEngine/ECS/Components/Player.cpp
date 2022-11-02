/*!*************************************************************************
****
\file Player.cpp
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

#include "Player.h"

namespace EM
{
	Player::Player() : mHealth{ 100 } {}

	bool Player::Deserialize(const rapidjson::Value& obj)
	{
		mHealth = obj["Health"].GetInt();
		return true;
	}
	bool Player::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Health");
		writer->Int(mHealth);
		writer->EndObject();
		return true;
	}
}
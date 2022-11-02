/*!*************************************************************************
****
\file Audio.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-9-2022
\brief  
****************************************************************************
***/
#include "ExoEngine/ECS/Components/Audio.h"

EM::Audio::Audio(): mAudiopath("")
{
}

bool EM::Audio::Deserialize(const rapidjson::Value& obj)
{
	mAudiopath = std::string(obj["Audioname"].GetString());
	return true;
}

bool EM::Audio::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();
	writer->Key("Audioname");
	writer->String(mAudiopath.c_str());
	writer->EndObject();
	return true;
}

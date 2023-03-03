/*!*************************************************************************
****
\file Audio.cpp
\author Cheung Jun Yin Matthew, Tan Ek Hern
\par DP email: j.cheung@digipen.edu, t.ekhern@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-10-2022
\brief  This file is used to serialize and deserialize audio files

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "ExoEngine/ECS/Components/Audio.h"

/*!*************************************************************************
Constructor for audio component
****************************************************************************/
EM::Audio::Audio() : AudioArr() {}


/*!*************************************************************************
Deserialize audio component
****************************************************************************/
bool EM::Audio::Deserialize(const rapidjson::Value& obj)
{
	for (int i = 0; (obj["ScriptName"].GetArray().Begin() + i) != obj["ScriptName"].GetArray().End(); ++i) {
		AudioPiece na;
		na.mAudioPath = obj["ScriptName"][i]["AudioPath"].GetString();
		na.mChannelGroup = static_cast<AudioType>(obj["ScriptName"][i]["Channel"].GetInt());
		na.is_Looping = obj["ScriptName"][i]["IsLooping"].GetInt();
		na.mChannel = 0;
		na.should_play = false;
		na.should_stop = false;
		na.is_Playing = false;
		AudioArr.push_back(na);
	}
	return true;
}

/*!*************************************************************************
Serialise audio component
****************************************************************************/
bool EM::Audio::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();
		writer->Key("AudioPiece");
		writer->StartArray();
		for (size_t i = 0; i < AudioArr.size(); ++i)
		{
			writer->Key("AudioPath");
			writer->String(AudioArr[i].mAudioPath.c_str());
			writer->Key("Channel");
			writer->Int(static_cast<int>(AudioArr[i].mChannelGroup));
			writer->Key("IsLooping");
			writer->Int(AudioArr[i].is_Looping);
		}
		writer->EndArray();
		writer->EndObject();
	return true;
}

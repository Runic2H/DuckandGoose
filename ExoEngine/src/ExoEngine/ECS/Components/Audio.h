/*!*************************************************************************
****
\file Audio.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-10-2022
\brief Header file for Audio.cpp

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IComponent.h"

namespace EM
{

	class Audio : public IComponent
	{
	public:
		enum class AudioType
		{
			NONE,
			MASTER,
			BGM,
			SFX
		};
		struct AudioPiece {
			std::string mAudioPath;
			AudioType mChannelGroup;
			bool is_Looping;
			bool should_play;
			bool is_Playing;
		};
		Audio();
		~Audio() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
		
		std::vector<AudioPiece> GetArr() { return AudioArr; }
		void SetArr(std::vector<AudioPiece> in) { AudioArr = in; }
		int GetSize() { return (int)AudioArr.size(); }
		AudioPiece& operator[](int i) { return AudioArr[i]; }

		/*!*************************************************************************
		Retrieves Component Entity ID
		****************************************************************************/
		Entity& GetComponentEntityID() { return entityID; }
		/*!*************************************************************************
		Sets Components Entity ID
		****************************************************************************/
		void SetComponentEntityID(Entity& entity) { entityID = entity; }

		//Audio component
		//	Singular piece of audio that can be set to play upon a specific event.
		//	Toggle looping.
		

	private:
		std::vector<AudioPiece> AudioArr;
	};
}
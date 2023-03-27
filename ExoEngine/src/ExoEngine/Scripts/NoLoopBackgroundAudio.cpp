/*!*************************************************************************
****
\file NoLoopBackgroundAudio.cpp
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief	Script for BGM

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "NoLoopBackgroundAudio.h"
#include "ExoEngine/Audio/AudioEngine.h"
#include "ExoEngine/ECS/Components/Audio.h"

namespace EM {
	NoLoopBackgroundAudio::NoLoopBackgroundAudio() {}

	NoLoopBackgroundAudio* NoLoopBackgroundAudio::Clone() const
	{
		return new NoLoopBackgroundAudio(*this);
	}

	void NoLoopBackgroundAudio::Start()
	{
		//check if it has an audio loaded 
		if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && (p_ecs.GetComponent<Audio>(GetScriptEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].is_Looping = true;
		}
	}

	void NoLoopBackgroundAudio::Update(float Frametime)
	{
		UNREFERENCED_PARAMETER(Frametime);
		if (p_ecs.HaveComponent<Audio>(GetScriptEntityID()) && (p_ecs.GetComponent<Audio>(GetScriptEntityID()).GetSize() > 0))
		{
			p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].is_Looping = false;
		}
	}

	void NoLoopBackgroundAudio::End()
	{
		p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].should_stop = true;
		p_ecs.GetComponent<Audio>(GetScriptEntityID())[0].is_Looping = false;
		delete this;
	}

	std::string NoLoopBackgroundAudio::GetScriptName()
	{
		return "NoLoopBackgroundAudio";
	}
}
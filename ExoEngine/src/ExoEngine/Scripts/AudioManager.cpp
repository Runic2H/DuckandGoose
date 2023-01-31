/*!*************************************************************************
****
\file AudioManager.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief	Script for Audio Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "AudioManager.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Audio Manager
    ****************************************************************************/
    AudioManager::AudioManager() {}
    /*!*************************************************************************
    Returns a new copy of AudioManager Script
    ****************************************************************************/
	AudioManager* AudioManager::Clone() const
	{
		return new AudioManager(*this);
	}
    /*!*************************************************************************
    Start State of AudioManager Script
    ****************************************************************************/
	void AudioManager::Start()
	{

	}
    /*!*************************************************************************
    Update Loop of AudioManager Script
    ****************************************************************************/
	void AudioManager::Update(float Frametime)
	{
        auto& audio = p_ecs.GetComponent<Audio>(GetScriptEntityID());
        for (int i = 0; i < audio.GetSize(); i++) {
            //check if sound is playing
            //set is_playing accordingly
            if (audio[i].should_play == true && audio[i].is_Playing == false) {
                //play sound
                audio[i].should_play = false;
                audio[i].is_Playing = true;
            }
            if (audio[i].is_Looping == true && audio[i].is_Playing == false) {
                //play sound
                audio[i].is_Playing = true;
            }
        }
	}
    /*!*************************************************************************
    End State for Audio Manager
    ****************************************************************************/
    void AudioManager::End()
    {
        delete this;
    }
    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string AudioManager::GetScriptName()
    {
        return "AudioManager";
    }
}
/*!*************************************************************************
****
\file DialogueManager.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Dialogue Manager

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "DialogueManager.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Dialogue Manager
    ****************************************************************************/
    DialogueManager::DialogueManager() : dialogueIndex{ 0 }, isAnimating{ false }, isFinishedAnimating{ false } {};

    /*!*************************************************************************
    Returns a new copy of DialogueManager Script
    ****************************************************************************/
    DialogueManager* DialogueManager::Clone() const
    {
        return new DialogueManager(*this);
    }

    /*!*************************************************************************
    Start State of DialogueManager Script
    ****************************************************************************/
    void DialogueManager::Start()
    {

    }

    /*!*************************************************************************
    Update Loop of Dialogue Manager Script
    ****************************************************************************/
    void DialogueManager::Update(float Frametime)
    {
        //check for finished animating
        if (isFinishedAnimating == false) {
            //check for animating
            if (isAnimating == false) {
                //if not finished and not animating, start animating
                isAnimating = true; 
            }
            //check for click
            if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT) && isAnimating == true) {
                //if click and animating, skip to end of animation
                isAnimating = false;
                isFinishedAnimating = true;
            }
        }
        else {
            //if click and animation finished, go to next dialogue
            if (p_Input->MousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
                dialogueIndex++;
            }
        }
        //check for empty dialogue segment. If empty means end of dialogue string. 
        //other trigger to start next dialogue strign? 
    }

    /*!*************************************************************************
    End State for Dialogue Manager
    ****************************************************************************/
    void DialogueManager::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string DialogueManager::GetScriptName()
    {
        return "DialogueManager";
    }
}
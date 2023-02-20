/*!*************************************************************************
****
\file LaserTurret.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Laser Turret

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "LaserTurret.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Laser Turret
    ****************************************************************************/
    LaserTurret::LaserTurret() : timeTilSpawn{ 1.f }, startTimeTilSpawn{ 1.f }, firingDuration{ 1.f }, startFiringDuration{ 1.f }, damage{2}, playerDetected{ false }, firing{ false } {};

    /*!*************************************************************************
    Returns a new copy of LaserTurret Script
    ****************************************************************************/
    LaserTurret* LaserTurret::Clone() const
    {
        return new LaserTurret(*this);
    }

    /*!*************************************************************************
    Start State of LaserTurret Script
    ****************************************************************************/
    void LaserTurret::Start()
    {

    }

    /*!*************************************************************************
    Update Loop of Player Controller Script
    ****************************************************************************/
    void LaserTurret::Update(float Frametime)
    {
        //check for player proximity
        if (playerDetected) {
            //check timer
            if (startTimeTilSpawn <= 0) {
                //set firing if timer is 0
                //fire laser and deal damage
                firing = true;
                //set collider to be alive
                auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
                col[0].is_Alive = true;
                //set firing duration
                startFiringDuration = firingDuration;
                //reset timer to max delay
                startTimeTilSpawn = timeTilSpawn;
            }
            else {
                //decrease timer
                startTimeTilSpawn -= Frametime;
            }
            if (firing) {
                //decrement firing duration
                startFiringDuration -= Frametime;
                if (startFiringDuration <= 0) {
                    //deactivate laser when time runs out
                    firing = false;
                    col[0].is_Alive = false;
                }
            }
        }
        //render laser?
        if (col[0].is_Alive == true) {

        }
    }

    /*!*************************************************************************
    End State for Laser Turret
    ****************************************************************************/
    void LaserTurret::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string LaserTurret::GetScriptName()
    {
        return "LaserTurret";
    }
}
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
    LaserTurret::LaserTurret() : firing{ false }, dmg{ 2 }, delay{ 1.f } {};

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
        //check timer
        //set firing if timer is 0
        //fire laser and deal damage
        //reset timer to max delay
        //decrease timer
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
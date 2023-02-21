/*!*************************************************************************
****
\file Gate Controller.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Gate Controller

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "GateController.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Gate Controller
    ****************************************************************************/
    GateController::GateController() : enemies{ 0 } {};

    /*!*************************************************************************
    Returns a new copy of GateController Script
    ****************************************************************************/
    GateController* GateController::Clone() const
    {
        return new GateController(*this);
    }

    /*!*************************************************************************
    Start State of GateController Script
    ****************************************************************************/
    void GateController::Start()
    {
        //how to initialise how many enemies in each section?
    }

    /*!*************************************************************************
    Update Loop of Gate Controller Script
    ****************************************************************************/
    void GateController::Update(float Frametime)
    {
        //check how many enemies killed
        //if no enemeies left, open gate
        if (enemies <= 0) {
            auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
            col[0].is_Alive = false;
        }
    }

    /*!*************************************************************************
    End State for Gate Controller
    ****************************************************************************/
    void GateController::End()
    {
        delete this;
    }

    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string GateController::GetScriptName()
    {
        return "GateController";
    }
}
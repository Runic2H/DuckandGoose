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
    GateController::GateController() {}

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
        p_ecs.GetComponent<Sprite>(GetScriptEntityID()).is_Animated = true;
        p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetIndex().x = 0;
        p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LASERGATE_BG_V2");
    }

    /*!*************************************************************************
    Update Loop of Gate Controller Script
    ****************************************************************************/
    void GateController::Update(float Frametime)
    {
        //if no enemeies left, open gate
        auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
        int aliveCount{};
        for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
        {
            if (p_ecs.HaveComponent<EnemyAttributes>(i))
            {
                if (p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive)
                {
                    ++aliveCount;
                }
            }
        }
        if (aliveCount == 0)
        {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).is_Animated = false;
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetIndex().x = p_ecs.GetComponent<Sprite>(GetScriptEntityID()).GetMaxIndex();
            col[0].is_Alive = false;
            col[1].is_Alive = false;
        }
        else
        {
            col[0].is_Alive = true;
            col[1].is_Alive = true;
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
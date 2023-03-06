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
    }

    /*!*************************************************************************
    Update Loop of Gate Controller Script
    ****************************************************************************/
    void GateController::Update(float Frametime)
    {
        //if no enemeies left, open gate
        auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
        for (Entity i = 0; i < p_ecs.GetTotalEntities(); ++i)
        {
            if (p_ecs.HaveComponent<EnemyAttributes>(i))
            {
                if (p_ecs.GetComponent<EnemyAttributes>(i).mIsAlive)
                {
                    p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("BG_LASERGATE000");
                    col[0].is_Alive = true;
                    return;
                }
                else 
                {
                    continue;
                }
            }
        }
        p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("BG_LASERGATE019");
        col[0].is_Alive = false;
        /*if (enemies <= 0) {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("BG_LASERGATE019");
            col[0].is_Alive = false;
            std::cout << "Gate Off" << std::endl;
        }
        else {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("BG_LASERGATE000");
            col[0].is_Alive = true;
            timer = 1.0f;
            std::cout << "Gate On" << std::endl;
        }*/
        ////failsafe
        //int f = 0;
        //for (int i = 0; i < (int)p_ecs.GetTotalEntities(); i++) {
        //    if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Enemy") {
        //        f++;
        //    }
        //}
        //if (f == 0) {
        //    col[0].is_Alive = false;
        //    std::cout << "Failsafe" << std::endl;
        //    p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("BG_LASERGATE019");
        //}
        //if (col[0].is_Alive == false && timer >= 0) {
        //    p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LASERGATE_BG");
        //    std::cout << "Animating Gate" << std::endl;
        //}
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
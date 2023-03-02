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
    GateController::GateController() : enemies{ 0 }, timer{ 0.0f } {};

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
        //check how many enemies killed
        timer -= Frametime;
        //if no enemeies left, open gate
        auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
        if (enemies <= 0) {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LaserBackOff");
            col[0].is_Alive = false;
            std::cout << "Gate Off" << std::endl;
        }
        else {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LaserBackOn");
            col[0].is_Alive = true;
            timer = 1.0f;
            std::cout << "Gate On" << std::endl;
        }
        //failsafe
        int f = 0;
        for (int i = 0; i < (int)p_ecs.GetTotalEntities(); i++) {
            if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "Enemy") {
                f++;
            }
        }
        if (f == 0) {
            col[0].is_Alive = false;
            std::cout << "Failsafe" << std::endl;
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LaserBackOff");
        }
        if (col[0].is_Alive == false && timer >= 0) {
            p_ecs.GetComponent<Sprite>(GetScriptEntityID()).SetTexture("LaserBackAnim");
            std::cout << "Animating Gate" << std::endl;
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
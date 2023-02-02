/*!*************************************************************************
****
\file PlayerController.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief	Script for HUD Controller

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "HUDController.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for HUD Controller
    ****************************************************************************/
    HUDController::HUDController() {}
    /*!*************************************************************************
    Returns a new copy of HUDController Script
    ****************************************************************************/
	HUDController* HUDController::Clone() const
	{
		return new HUDController(*this);
	}
    /*!*************************************************************************
    Start State of HUDController Script
    ****************************************************************************/
	void HUDController::Start()
	{

	}
    /*!*************************************************************************
    Update Loop of HUDController Script
    ****************************************************************************/
	void HUDController::Update(float Frametime)
	{
        auto& pComp = p_ecs.GetComponent<HUDComponent>(GetScriptEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetScriptEntityID());
        auto& pSprite = p_ecs.GetComponent<Sprite>(GetScriptEntityID());
        //get camera position
        vec2D camPos = vec2D(camera.GetPosition().x, camera.GetPosition().y);
        //update position
        pTrans.SetPos(camPos + pComp.GetOffset());

        if (pComp.GetType() == HUDComponent::ElementType::Static) {    
            //do ???
        }
        else if (pComp.GetType() == HUDComponent::ElementType::HealthBar) {
            //update health bar value
            //update scale
            pTrans.SetScale(vec2D(1,1));
        }
        else if (pComp.GetType() == HUDComponent::ElementType::BlockIcon) {
            //check for timing of cooldown
            //update alpha
            pSprite.SetAlpha(1);
        }
        else if (pComp.GetType() == HUDComponent::ElementType::ChargeAtk) {
            //check if charge attack is being triggered
            if (1) {
                pSprite.SetAlpha(1);
            }
            else {
                pSprite.SetAlpha(0);
            }
        }
        else if (pComp.GetType() == HUDComponent::ElementType::Text) {
            //update atk value
            int atk = 0;
            //get combo bonus value
            int bonus = 0;
            pComp.SetAtk((std::to_string(atk) + " + " + std::to_string(bonus)));
            //update def value
            int def = 0;
            pComp.SetDef((std::to_string(def)));
            //update spd value
            int spd = 0;
            pComp.SetSpd((std::to_string(spd)));
            //update combo value
            int combo = 0;
            pComp.SetCombo(("Combo " + std::to_string(combo)));
            //add combo value
        }
	}
    /*!*************************************************************************
    End State for HUDController
    ****************************************************************************/
    void HUDController::End()
    {
        delete this;
    }
    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string HUDController::GetScriptName()
    {
        return "HUDController";
    }
}
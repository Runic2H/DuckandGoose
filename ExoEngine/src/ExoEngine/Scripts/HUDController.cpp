/*!*************************************************************************
****
\file HUDController.cpp
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
        UNREFERENCED_PARAMETER(Frametime);
        auto& pComp = p_ecs.GetComponent<HUDComponent>(GetScriptEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetScriptEntityID());
        auto& pSprite = p_ecs.GetComponent<Sprite>(GetScriptEntityID());
        auto& pStats = p_ecs.GetComponent<Attributes>(GetScriptEntityID());
        //get camera position
        vec2D camPos = vec2D(Graphic::camera.GetPosition().x, Graphic::camera.GetPosition().y);
        //update position
        pTrans.SetPos(camPos + pComp.GetOffset());
        //std::cout << "Cam Pos: " << Graphic::camera.GetPosition().x << ", " << Graphic::camera.GetPosition().y << "\n";
        //std::cout << "HUD Pos: " << pTrans.GetPos().x << ", " << pTrans.GetPos().y << "\n";
        if (pComp.GetType() == HUDComponent::ElementType::Static) {    
            //do ???
        }
        else if (pComp.GetType() == HUDComponent::ElementType::HealthBar) {
            //update scale
            pTrans.SetScale(0.75f * (float)pStats.GetHealth() / 100, pTrans.GetScale().y);
            pTrans.SetPos(static_cast<float>(camPos.x + pComp.GetOffset().x - 0.32 * (100.f - (float)pStats.GetHealth())) / 100.0f, camPos.y + pComp.GetOffset().y);
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
            int atk = pStats.GetDamage();
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
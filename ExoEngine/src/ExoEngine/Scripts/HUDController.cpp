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
    HUDController::HUDController() : mCurrCooldown{ 0.0f } {}
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
        int hp = 0;
        int maxhp = 0;
        int atk = 0;
        mCurrCooldown -= Frametime;
        if (mCurrCooldown <= 0) {
            mCurrCooldown = 0;
        }
        
        //get player's stats
        for (Entity i = 0; i < p_ecs.GetTotalEntities(); i++) {
            if (p_ecs.HaveComponent<NameTag>(i) && p_ecs.GetComponent<NameTag>(i).GetNameTag() == "player") {
                hp = p_ecs.GetComponent<PlayerAttributes>(i).mHealth;
                maxhp = p_ecs.GetComponent<PlayerAttributes>(i).mMaxHealth;
                atk = p_ecs.GetComponent<PlayerAttributes>(i).mDamage;
            }
        }
        if (p_ecs.HaveComponent<HUDComponent>(GetScriptEntityID()) && p_ecs.HaveComponent<Transform>(GetScriptEntityID()) && p_ecs.HaveComponent<Sprite>(GetScriptEntityID()))
        {
            auto& pComp = p_ecs.GetComponent<HUDComponent>(GetScriptEntityID());
            auto& pTrans = p_ecs.GetComponent<Transform>(GetScriptEntityID());
            auto& pSprite = p_ecs.GetComponent<Sprite>(GetScriptEntityID());

            //get camera position
            vec2D camPos = vec2D(Graphic::camera.GetPosition().x, Graphic::camera.GetPosition().y);
            //update position
            pTrans.SetPos(camPos + pComp.GetOffset());
            //std::cout << "Cam Pos: " << Graphic::camera.GetPosition().x << ", " << Graphic::camera.GetPosition().y << "\n";
            //std::cout << "HUD Pos: " << pTrans.GetPos().x << ", " << pTrans.GetPos().y << "\n";
            if (pComp.GetType() == HUDComponent::ElementType::Static) {
                pTrans.SetPos(static_cast<float>(camPos.x + pComp.GetOffset().x), camPos.y + pComp.GetOffset().y);
            }
            else if (pComp.GetType() == HUDComponent::ElementType::HealthBar) {
                //update scale
                pTrans.SetScale((float)hp / (float)maxhp, pTrans.GetScale().y);
                pTrans.SetPos(static_cast<float>(camPos.x + pComp.GetOffset().x) + ((float)hp / (float)maxhp / 2.325f), camPos.y + pComp.GetOffset().y);
            }
            else if (pComp.GetType() == HUDComponent::ElementType::BlockBar) {
                //check for timing of cooldown
                float maxCooldown = 0;
                if (1) {
                    mCurrCooldown = maxCooldown;
                }
                //update alpha
                pTrans.SetScale(mCurrCooldown / maxCooldown, pTrans.GetScale().y);
                pTrans.SetPos(static_cast<float>(camPos.x + pComp.GetOffset().x) + (mCurrCooldown / maxCooldown / 2.325f), camPos.y + pComp.GetOffset().y);
            }
            else if (pComp.GetType() == HUDComponent::ElementType::DashBar) {
                //check for timing of cooldown
                float maxCooldown = 0;
                //update alpha
                pTrans.SetScale(mCurrCooldown / maxCooldown, pTrans.GetScale().y);
                pTrans.SetPos(static_cast<float>(camPos.x + pComp.GetOffset().x) + (mCurrCooldown / maxCooldown / 2.325f), camPos.y + pComp.GetOffset().y);
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
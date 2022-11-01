/*!*************************************************************************
****
\file			PlayerInput.cpp
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			26-10-2022
\brief			This file contains the necessary function definitions player 
                movement

****************************************************************************
***/
#include "empch.h"
#include "PlayerInput.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"


namespace EM {
    //extern ECS ecs;
    void PlayerInput::Init() {
    }
	void PlayerInput::Update(float dt) {
        for (auto const& player : mEntities) {
            auto& pRigid = p_ecs.GetComponent<RigidBody>(player);
            auto& pTrans = p_ecs.GetComponent<Transform>(player);
            if (p_Input->isKeyPressed(GLFW_KEY_UP) || p_Input->isKeyPressed(GLFW_KEY_DOWN) || p_Input->isKeyPressed(GLFW_KEY_RIGHT) || p_Input->isKeyPressed(GLFW_KEY_LEFT)) {
                if (p_Input->isKeyPressed(GLFW_KEY_UP)) {
                    vec2D vel(0, 10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_UP) && p_Input->isKeyPressed(GLFW_KEY_RIGHT)) {
                    vec2D vel(10.f, 10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_RIGHT)) {
                    vec2D vel(10.f, 0);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_RIGHT) && p_Input->isKeyPressed(GLFW_KEY_DOWN)) {
                    vec2D vel(10.f, -10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_DOWN)) {
                    vec2D vel(0, -10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_DOWN) && p_Input->isKeyPressed(GLFW_KEY_LEFT)) {
                    vec2D vel(-10.f, -10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT)) {
                    vec2D vel(-10.f, 0);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
                if (p_Input->isKeyPressed(GLFW_KEY_LEFT) && p_Input->isKeyPressed(GLFW_KEY_UP)) {
                    vec2D vel(-10.f, 10.f);
                    pRigid.SetVel(phys.accelent(pRigid.GetVel(), vel, dt));
                }
            }
            else {
                pRigid.SetVel(phys.friction(pRigid.GetVel(), dt));
            }
            //camera.SetPosition({pTrans.GetPos().x, pTrans.GetPos().y, 0.0f });
            vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
            pRigid.SetNextPos(nextPos);
            //pTrans.SetPos(pRigid.GetNextPos());
        }
    }
	void PlayerInput::End() {
    }
}
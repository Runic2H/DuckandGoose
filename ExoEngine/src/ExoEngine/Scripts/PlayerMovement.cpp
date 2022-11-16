/*!*************************************************************************
****
\file PlayerMovement.cpp
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for basic movement for player

****************************************************************************
***/

#include "PlayerMovement.h"
namespace EM
{

    PlayerMovement* PlayerMovement::Clone() const
	{
        return new PlayerMovement(*this);
	}
	void PlayerMovement::Start() {
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetEntityID());
        pTrans.SetPos(vec2D(0,0));
        pRigid.SetVel(vec2D(0,0));
    }

	void PlayerMovement::Update(float Frametime)
	{
        auto& pRigid = p_ecs.GetComponent<RigidBody>(GetEntityID());
        auto& pTrans = p_ecs.GetComponent<Transform>(GetEntityID());
        vec2D vel = vec2D(0,0);
        float mag = length(pRigid.GetAccel());
        bool flag = false;
        if (p_Input->isKeyPressed(GLFW_KEY_UP)) {
            vel.y += 1;
            flag = true;
        }
        if (p_Input->isKeyPressed(GLFW_KEY_RIGHT)) {
            vel.x += 1;
            flag = true;
        }
        if (p_Input->isKeyPressed(GLFW_KEY_DOWN)) {
            vel.y -= 1;
            flag = true;
        }
        if (p_Input->isKeyPressed(GLFW_KEY_LEFT)) {
            vel.x -= 1;
            flag = true;
        }
        vec2D currVel = pRigid.GetVel();
        if (flag) {
            Normalize(vel, vel);
            vel = vel * mag;
            currVel = phys.accelent(currVel, vel, Frametime);
        }
        else {
            currVel = phys.friction(currVel, Frametime);
        }
        if (currVel.x > -99 && currVel.y < 99) {
            pRigid.SetVel(currVel);
        }
        //camera.SetPosition({pTrans.GetPos().x, pTrans.GetPos().y, 0.0f });
        vec2D nextPos = pTrans.GetPos() + pRigid.GetVel();
        pRigid.SetNextPos(nextPos);
	}
	void PlayerMovement::End()
	{
        delete this;
	}

    std::string PlayerMovement::GetScriptName() { return "PlayerMovement"; }
}
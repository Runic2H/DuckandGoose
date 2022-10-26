/*!*************************************************************************
****
\file			enemy_movement.h
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			26-10-2022
\brief			This file contains the necessary functions for enemy movement

****************************************************************************
***/
#pragma once
#include "physics.h"
#include "ExoEngine/ECS/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"
enum class E_State {
    patrol,
    chase,
    attack
};

namespace EM {
    class Enemy_Movement : public System {
        public:
            virtual std::string GetName() { return "Enemy_Movement"; }

            virtual void Init() override;
            virtual void Update(float dt) override;
            virtual void End() override;
        private: 
            
	};
}
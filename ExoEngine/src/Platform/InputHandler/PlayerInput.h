/*!*************************************************************************
****
\file			PlayerInput.h
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			26-10-2022
\brief			This file contains the necessary functions for player input

****************************************************************************
***/
#pragma once
#include "ExoEngine/Math/Physics.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"
#include "../../Platform/Graphics/Camera2D.h"

namespace EM {
    class PlayerInput : public System {
        public:
            virtual std::string GetName() { return "Player_Input"; }

            virtual void Init() override;
            virtual void Update(float dt) override;
            virtual void End() override;
        private: 
            Camera2D camera = { -1.0f, 1.0f, -1.0f , 1.0f };
            entityPhysics phys;
	};
}
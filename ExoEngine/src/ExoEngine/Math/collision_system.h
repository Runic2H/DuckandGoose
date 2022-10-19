/*!*************************************************************************
****
\file			collision_system.h
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			14-10-2022
\brief			This file contains the necessary functions for collision

****************************************************************************
***/
#pragma once
#include "RigidBody.h"
#include "physics.h"
#include "ExoEngine/ECS/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
    class CollisionSystem : public System {
        public:
            virtual std::string GetName() { return "Collision"; }

            virtual void Init() override;
            virtual void Update(float dt) override;
            virtual void End() override;
        private: 
            
	};
}
/*!*************************************************************************
****
\file			CollisionSystem.h
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			14-10-2022
\brief			This file contains the necessary functions for collision

****************************************************************************
***/
#pragma once
#include "Physics.h"
<<<<<<<< HEAD:ExoEngine/src/ExoEngine/Math/CollisionSystem.h
#include "ExoEngine/ECS/Components.h"
========
#include "ExoEngine/ECS/Components/Components.h"
>>>>>>>> a2c28223adcbb8c8baa1c79e249d860e41369b43:ExoEngine/src/Platform/Physics/CollisionSystem.h
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
    class CollisionSystem : public System {
    public:
        virtual std::string GetName() { return "Collision"; }

<<<<<<<< HEAD:ExoEngine/src/ExoEngine/Math/CollisionSystem.h
            virtual void Init() override;
            virtual void Update(float dt) override;
            virtual void End() override;
        private: 
            entityCollision ecm;
	};
========
        virtual void Init() override;
        virtual void Update(float dt) override;
        virtual void End() override;
    private:
        entityCollision ecm;
    };
>>>>>>>> a2c28223adcbb8c8baa1c79e249d860e41369b43:ExoEngine/src/Platform/Physics/CollisionSystem.h
}
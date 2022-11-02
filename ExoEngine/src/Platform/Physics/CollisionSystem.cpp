/*!*************************************************************************
****
\file			CollisionSystem.cpp
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			14-10-2022
\brief			This file contains the necessary function definitions for
                collision

****************************************************************************
***/
#include "empch.h"
#include "CollisionSystem.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/Math/Physics.h"

namespace EM {
    //extern ECS ecs;
    void CollisionSystem::Init() {
        //check which component has collision and add it to array
        //assign collider to rigidbody component
    }
    void CollisionSystem::Update(float dt) {
        Timer::GetInstance().Start(Systems::COLLISION);
        Timer::GetInstance().GetDT(Systems::COLLISION);
        //iterate through array of entities
        int k = 0;
        for (auto const& i : mEntities) {
            //make j index i+1
            int l = 0;
            for (auto const& j : mEntities) {
                if (i != j && l > k) {
                    auto& col1 = p_ecs.GetComponent<Collider>(i);
                    auto& col2 = p_ecs.GetComponent<Collider>(j);
                    auto& trans1 = p_ecs.GetComponent<Transform>(i);
                    auto& trans2 = p_ecs.GetComponent<Transform>(j);
                    Collider::ColliderType e1 = col1.GetCollider();
                    Collider::ColliderType e2 = col2.GetCollider();
                    col1.SetHit(0);
                    col2.SetHit(0);
                    if (e1 == Collider::ColliderType::circle) {
                        if (e2 == Collider::ColliderType::circle) {
                            if (ecm.simpleCircleCircle(trans1.GetPos(), trans2.GetPos(), col1.GetRad(), col2.GetRad())) {
                                col1.SetHit(1);
                                col2.SetHit(1);
                                std::cout << "hit\n";
                            }
                        }
                        if (e2 == Collider::ColliderType::rect) {
                            vec2D max = trans2.GetPos() + col2.GetMax();
                            vec2D min = trans2.GetPos() + col2.GetMin();
                            if (ecm.simpleCircleRect(trans1.GetPos(), col1.GetRad(), max, min, trans2.GetPos())) {
                                col1.SetHit(1);
                                col2.SetHit(1);
                                std::cout << "hit\n";
                            }
                        }
                    }
                    else if (e1 == Collider::ColliderType::rect) {
                        if (e2 == Collider::ColliderType::circle) {
                            vec2D max = trans1.GetPos() + col1.GetMax();
                            vec2D min = trans1.GetPos() + col1.GetMin();
                            if (ecm.simpleCircleRect(trans2.GetPos(), col2.GetRad(), max, min, trans1.GetPos())) {
                                col1.SetHit(1);
                                col2.SetHit(1);
                                std::cout << "hit\n";
                            }
                        }
                        if (e2 == Collider::ColliderType::rect) {
                            vec2D max1 = trans1.GetPos() + col1.GetMax();
                            vec2D min1 = trans1.GetPos() + col1.GetMin();
                            vec2D max2 = trans2.GetPos() + col2.GetMax();
                            vec2D min2 = trans2.GetPos() + col2.GetMin();
                            if (ecm.simpleRectRect(max1, min1, max2, min2)) {
                                col1.SetHit(1);
                                col2.SetHit(1);
                                std::cout << "hit\n";
                            }
                        }
                    }
                }
                l++;
            }
            k++;
        }

        Timer::GetInstance().Update(Systems::COLLISION);
    }
    void CollisionSystem::End() {
        //remove all entities from array
    }
}
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
        (void)dt;
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
                    auto& rigid1 = p_ecs.GetComponent<RigidBody>(i);
                    auto& rigid2 = p_ecs.GetComponent<RigidBody>(j);
                    Collider::ColliderType e1 = col1.GetCollider();
                    Collider::ColliderType e2 = col2.GetCollider();
                    col1.SetHit(0);
                    col2.SetHit(0);
                    vec2D offset1 = rigid1.GetNextPos() + col1.GetOffset();
                    vec2D offset2 = rigid2.GetNextPos() + col2.GetOffset();
                    if (e1 == Collider::ColliderType::circle) {
                        if (e2 == Collider::ColliderType::circle) {
                            if (ecm.simpleCircleCircle(offset1, offset2, col1.GetRad(), col2.GetRad())) {
                                col1.SetHit(1);
                                vec2D norm1 = offset1 - offset2;
                                Normalize(norm1, norm1);
                                col1.SetNormal(norm1);
                                col2.SetHit(1);
                                vec2D norm2 = offset2 - offset1;
                                Normalize(norm2, norm2);
                                col2.SetNormal(norm2);
                                std::cout << "hit\n";
                            }
                        }
                        if (e2 == Collider::ColliderType::rect) {
                            vec2D max = offset2 + col2.GetMax();
                            vec2D min = offset2 + col2.GetMin();
                            if (ecm.simpleCircleRect(offset1, col1.GetRad(), max, min, offset2)) {
                                col1.SetHit(1);
                                vec2D norm1 = offset1 - offset2;
                                Normalize(norm1, norm1);
                                col1.SetNormal(norm1);
                                col2.SetHit(1);
                                vec2D norm2 = offset2 - offset1;
                                Normalize(norm2, norm2);
                                col2.SetNormal(norm2);
                                std::cout << "hit\n";
                            }
                        }
                    }
                    else if (e1 == Collider::ColliderType::rect) {
                        if (e2 == Collider::ColliderType::circle) {
                            vec2D max = offset1 + col1.GetMax();
                            vec2D min = offset1 + col1.GetMin();
                            if (ecm.simpleCircleRect(offset2, col2.GetRad(), max, min, offset1)) {
                                col1.SetHit(1);
                                vec2D norm1 = offset1 - offset2;
                                Normalize(norm1, norm1);
                                col1.SetNormal(norm1);
                                col2.SetHit(1);
                                vec2D norm2 = offset2 - offset1;
                                Normalize(norm2, norm2);
                                col2.SetNormal(norm2);
                                std::cout << "hit\n";
                            }
                        }
                        if (e2 == Collider::ColliderType::rect) {
                            vec2D max1 = offset1 + col1.GetMax();
                            vec2D min1 = offset1 + col1.GetMin();
                            vec2D max2 = offset2 + col2.GetMax();
                            vec2D min2 = offset2 + col2.GetMin();
                            if (ecm.simpleRectRect(max1, min1, max2, min2)) {
                                vec2D line;
                                if(max1.x >= min2.x && min1.x <= max2.x) {
                                    line.y = 1;
                                    if (min1.y <= max2.y) {
                                        line.y = -1;
                                    }
                                }
                                if(max1.y >= min2.y && min1.y <= max2.y) {
                                    line.x = 1;
                                    if (max1.x <= min2.x) {
                                        line.x = -1;
                                    }
                                }
                                col1.SetHit(1);
                                col1.SetNormal(line);
                                col2.SetHit(1);
                                col2.SetNormal(line * -1);
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
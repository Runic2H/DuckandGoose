/*!*****************************************************************************
\file CollisionSystem.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: csd2125
\par Section: a
\par 
\date 14-10-2022
\brief  This file contains the function definitions for the collision system
 
 Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
*******************************************************************************/
#include "empch.h"
#include "CollisionSystem.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/Math/Physics.h"

namespace EM {
    /*!*************************************************************************
	This function initialises the system. As there are no data members that require
	initialization, this function is empty
	****************************************************************************/
    void CollisionSystem::Init() {}
    /*!*************************************************************************
	This function runs the logic of the system. It checks the list of entities with
    a collision component in pairs to see which of them are colliding. If two objects
    are colliding, collision response is dictated by the type of collider the object
    has
	****************************************************************************/
    void CollisionSystem::Update(float dt) {
        (void)dt;
        Timer::GetInstance().Start(Systems::COLLISION);
        Timer::GetInstance().GetDT(Systems::COLLISION);
        //iterate through array of entities
        int k = 0;
        for (auto const& i : mEntities) {
            auto& col1 = p_ecs.GetComponent<Collider>(i);
            for (int a = 0; a < 2; a++) {
                col1[a].mHit = 0;
                col1[a].mCollisionNormal = vec2D();
            }
        }
        for (auto const& i : mEntities) {
            int l = 0;
            for (auto const& j : mEntities) {
                if (i != j && l > k) {
                    auto& col1 = p_ecs.GetComponent<Collider>(i);
                    auto& col2 = p_ecs.GetComponent<Collider>(j);
                    auto& rigid1 = p_ecs.GetComponent<RigidBody>(i);
                    auto& rigid2 = p_ecs.GetComponent<RigidBody>(j);
                    //broad phase sweep
                    if (distance(rigid1.GetNextPos(), rigid2.GetNextPos()) < 3) {
                        for (int a = 0; a < 2; a++) {
                            for (int b = 0; b < 2; b++) {
                                Collider::ColliderType e1 = col1[a].mCol;
                                Collider::ColliderType e2 = col2[b].mCol;
                                vec2D offset1 = rigid1.GetNextPos() + col1[a].mOffset;
                                vec2D offset2 = rigid2.GetNextPos() + col2[b].mOffset;
                                //std::cout << (int)e1 << ", " << (int)e2 << "\n";
                                if (col1[a].is_Alive && col2[b].is_Alive) {
                                    if (e1 == Collider::ColliderType::circle) {
                                        if (e2 == Collider::ColliderType::circle) {
                                            if (ecm.simpleCircleCircle(offset1, offset2, col1[a].mRadius, col2[b].mRadius)) {
                                               // std::cout << "Collision Circle-Circle\n";
                                                col1[a].mHit = 1;
                                                vec2D norm1 = offset1 - offset2;
                                                Normalize(norm1, norm1);
                                                //std::cout << &col1 << "\n";
                                                //std::cout << "Norm1: " << norm1.x << ", " << norm1.y << "\n";
                                                col1[a].mCollisionNormal = norm1;
                                                //std::cout << "ColNorm1: " << col1[a].mCollisionNormal.x << ", " << col1[a].mCollisionNormal.y << "\n";
                                                col2[b].mHit = 1;
                                                vec2D norm2 = offset2 - offset1;
                                                Normalize(norm2, norm2);
                                                col2[b].mCollisionNormal = norm2;
                                                // std::cout << "hit\n";
                                            }
                                        }
                                        if (e2 == Collider::ColliderType::bubble) {
                                            if (ecm.simpleCircleCircle(offset1, offset2, col1[a].mRadius, col2[b].mRadius)) {
                                                // std::cout << "Collision Circle-Circle\n";
                                                col2[b].mHit = 3;
                                            }
                                        }
                                        if (e2 == Collider::ColliderType::rect) {
                                            vec2D max2 = offset2 + col2[b].mMax;
                                            vec2D min2 = offset2 - col2[b].mMin;
                                            if (ecm.simpleCircleRect(offset1, col1[a].mRadius, max2, min2, offset2)) {
                                                //std::cout << "Collision Circle-Rect\n";
                                                col1[a].mHit = 2;
                                                vec2D norm1 = offset1 - offset2;
                                                Normalize(norm1, norm1);
                                                col1[a].mCollisionNormal = norm1;
                                                col2[b].mHit = 1;
                                                vec2D norm2 = offset2 - offset1;
                                                Normalize(norm2, norm2);
                                                col2[b].mCollisionNormal = norm2;
                                                // std::cout << "hit\n";
                                            }
                                        }
                                        if (e2 == Collider::ColliderType::box) {
                                            vec2D max2 = offset2 + col2[b].mMax;
                                            vec2D min2 = offset2 - col2[b].mMin;
                                            if (ecm.simpleCircleRect(offset1, col1[a].mRadius, max2, min2, offset2)) {
                                                vec2D norm1;
                                                if (offset1.x - col1[b].mRadius <= min2.x) {
                                                    norm1.x = -1;
                                                }
                                                else if (offset1.x + col1[b].mRadius >= max2.x) {
                                                    norm1.x = 1;
                                                }
                                                if (offset1.y - col1[b].mRadius <= max2.y) {
                                                    norm1.y = -1;
                                                }
                                                else if (offset1.y + col1[b].mRadius >= min2.y) {
                                                    norm1.y = 11;
                                                }
                                                Normalize(norm1, norm1);
                                                col1[b].mHit = 1;
                                                col1[b].mCollisionNormal = norm1;
                                            }
                                        }
                                    }
                                    else if (e1 == Collider::ColliderType::rect) {
                                        if (e2 == Collider::ColliderType::circle) {
                                            vec2D max1 = offset1 + col1[a].mMax;
                                            vec2D min1 = offset1 - col1[a].mMin;
                                            if (ecm.simpleCircleRect(offset2, col2[b].mRadius, max1, min1, offset1)) {
                                                //std::cout << "Collision Rect-Circle\n";
                                                col1[a].mHit = 1;
                                                vec2D norm1 = offset1 - offset2;
                                                Normalize(norm1, norm1);
                                                col1[a].mCollisionNormal = norm1;
                                                col2[b].mHit = 2;
                                                vec2D norm2 = offset2 - offset1;
                                                Normalize(norm2, norm2);
                                                col2[b].mCollisionNormal = norm2;
                                                // std::cout << "hit\n";
                                            }
                                        }
                                        if (e2 == Collider::ColliderType::rect) {
                                            vec2D max1 = offset1 + col1[a].mMax;
                                            vec2D min1 = offset1 - col1[a].mMin;
                                            vec2D max2 = offset2 + col2[b].mMax;
                                            vec2D min2 = offset2 - col2[b].mMin;
                                            if (ecm.simpleRectRect(max1, min1, max2, min2)) {
                                                vec2D colmax1 = offset1 + col1[a].mMax * 0.8f;
                                                vec2D colmin1 = offset1 - col1[a].mMin * 0.8f;
                                                vec2D colmax2 = offset2 + col2[b].mMax * 0.8f;
                                                vec2D colmin2 = offset2 - col2[b].mMin * 0.8f;
                                                vec2D line;
                                                if (max1.x >= min2.x && max1.x < colmin2.x) {
                                                    line.x = -1.f;
                                                }
                                                else if (max2.x >= min1.x && max2.x < colmin1.x) {
                                                    line.x = 1.f;
                                                }
                                                if (max1.y < colmin2.y && (max1.x > colmin2.x || min1.x < colmax2.x)) {
                                                    line.y = -1.f;
                                                }
                                                else if (max2.y < colmin1.y && (max2.x > colmin1.x || min2.x < colmax1.x)) {
                                                    line.y = 1.f;
                                                }
                                                col1[a].mHit = 1;
                                                col1[a].mCollisionNormal = line;
                                                col2[b].mHit = 1;
                                                col2[b].mCollisionNormal = (line * -1);
                                                //std::cout << "hit\n";
                                            }
                                        }
                                    }
                                    //playable area bounding box to be implemented
                                    else if (e1 == Collider::ColliderType::box) {
                                        if (e2 == Collider::ColliderType::circle) {
                                            vec2D max1 = offset1 + col1[a].mMax;
                                            vec2D min1 = offset1 - col1[a].mMin;
                                            if (ecm.simpleCircleRect(offset2, col2[b].mRadius, max1, min1, offset1)) {
                                                //std::cout << "Collision Rect-Circle\n";
                                                vec2D norm2;
                                                if (offset2.x - col2[b].mRadius <= min1.x) {
                                                    norm2.x = -1;
                                                }
                                                else if (offset2.x + col2[b].mRadius >= max1.x) {
                                                    norm2.x = 1;
                                                }
                                                if (offset2.y - col2[b].mRadius <= max1.y) {
                                                    norm2.y = -1;
                                                }
                                                else if (offset2.y + col2[b].mRadius >= min1.y) {
                                                    norm2.y = 1;
                                                }
                                                Normalize(norm2, norm2);
                                                col2[b].mHit = 1;
                                                col2[b].mCollisionNormal = norm2;
                                                // std::cout << "hit\n";
                                            }
                                        }
                                    }
                                    else if (e1 == Collider::ColliderType::bubble) {
                                        if (e2 == Collider::ColliderType::circle) {
                                            if (ecm.simpleCircleCircle(offset1, offset2, col1[a].mRadius, col2[b].mRadius)) {
                                                // std::cout << "Collision Circle-Circle\n";
                                                col1[a].mHit = 3;
                                            }
                                        }
                                    }
                                }
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
    /*!*************************************************************************
	This function ends the system. As there are no data members that require
	initialization, there are no data members that need to be un-initialised. 
	Therefore this function is empty
	****************************************************************************/
    void CollisionSystem::End() {}
}
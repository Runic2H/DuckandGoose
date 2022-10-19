/*!*************************************************************************
****
\file			collision_system.cpp
\author			Tan Ek Hern
\par DP email:	t.ekhern@digipen.edu
\par Course:	Gam200
\section		A
\date			14-10-2022
\brief			This file contains the necessary function definitions for 
                collision

****************************************************************************
***/
#include "collision_system.h"
#include "../ECS/Components.h"

namespace EM {
    enum Col_Type
    {
        cone, //---------Cone
        circle, //-------Circle
        line, //---------LineSegment
        rect //----------AABB
    };
    void CollisionSystem::Init() {
        //check which component has collision and add it to array
        //assign collider to rigidbody component
    }
	void CollisionSystem::Update(float dt) {
        //iterate through array of entities
        for (auto i = mEntities.begin(); (i+1) != mEntities.end(); i++) {
            //make j index i+1
            for (auto j = (i+1); j != mEntities.end(); j++) {
                auto trans1 = ecs.GetComponent<Transform>(i);
                auto trans2 = ecs.GetComponent<Transform>(j);
                if (trans1 && trans2) {
                    vec2D ent1pos = trans1.GetPos();
                    vec2D ent2pos = trans2.GetPos();
                    //do a distance check disqualifier
                    if (distance(ent1pos, ent2pos) < 4) {
                        //check entity 1 and 2 collider
                        auto rigid1 = ecs.GetComponent<RigidBody>(i);
                        auto rigid2 = ecs.GetComponent<RigidBody>(j);
                        if (rigid1 && rigid2) {
                            Col_Type e1 = rigid1.GetCollider();
                            Col_Type e2 = rigid2.GetCollider();
                            //apply collision based on entity 1 and 2 collider types
                            //apply appropriate collision response
                            if (e1 == Col_Type::cone) {
                                if (e2 == Col_Type::circle) {
                                    circle_bound ent1;
                                    ent1.center = ent1pos;
                                    ent1.radius = rigid1.GetMax().value.x - ent1pos.value.x;
                                    circle_bound ent2;
                                    ent1.center = ent2pos;
                                    ent1.radius = rigid2.GetMax().value.x - ent2pos.value.x;
                                    bool lr;
                                    if (rigid1.GetVel().value.x < 0) {
                                        lr = 0;
                                    }
                                    else {
                                        lr = 1;
                                    }
                                    //check which attack variant for angles

                                    if (entityCollision::coneCollision(ent1, const int startAngle, const int endAngle, lr, ent2)) {
                                        //hit detected. take damage
                                    }
                                }
                            }
                            else if (e1 == Col_Type::circle) {
                                circle_bound ent1;
                                ent1.center = ent1pos;
                                ent1.radius = rigid1.GetMax().value.x - ent1pos.value.x;
                                if (e2 == Col_Type::circle) {
                                    circle_bound ent2;
                                    ent1.center = ent2pos;
                                    ent1.radius = rigid2.GetMax().value.x - ent2pos.value.x;
                                    vec2D ent1colpt;
                                    vec2D ent2colpt;
                                    float coltime;
                                    if (entityCollision::objCollision(ent1, rigid1.GetVel(), ent2, rigid2.GetVel(), ent1colpt, ent2colpt, coltime)) {
                                        vec2D colnorm = ent1colpt - ent2pos;
                                        Normalize(colnorm, colnorm);
                                        vec2D ent1newvel = rigid1.GetVel();
                                        vec2D ent2newvel = rigid2.GetVel();
                                        vec2D ent1nextpos = rigid1.GetNextPos();
                                        vec2D ent2nextpos = rigid2.GetNextPos();
                                        entityCollision::circleBounce(colnorm, coltime, rigid1.GetVel(), ent1colpt, rigid2.GetVel(), ent2colpt, ent1newvel, ent1nextpos, ent2newvel, ent2nextpos);
                                        rigid1.SetVel(ent1newvel);
                                        rigid2.SetVel(ent2newvel);
                                        rigid1.SetNextPos(ent1nextpos);
                                        rigid2.SetNextPos(ent2nextpos);
                                    }
                                }
                                else if (e2 == Col_Type::cone) {
                                    circle_bound ent2;
                                    ent1.center = ent2pos;
                                    ent1.radius = rigid2.GetMax().value.x - ent2pos.value.x;
                                    bool lr;
                                    if (rigid2.GetVel().value.x < 0) {
                                        lr = 0;
                                    }
                                    else {
                                        lr = 1;
                                    }
                                    //check which attack variant for angles

                                    if (entityCollision::coneCollision(ent1, const int startAngle, const int endAngle, lr, ent2)) {
                                        //hit detected. take damage
                                    }
                                }
                                else if (e2 == Col_Type::line) {
                                    wall wall2;
                                    wall2.p0 = rigid2.GetMin();
                                    wall2.p1 = rigid2.GetMax();
                                    vec2D temp = wall2.p1 - wall2.p0;
                                    wall2.normal.value.x = temp.value.y;
                                    wall2.normal.value.y = -temp.value.x;
                                    Normalize(wall2.normal, wall2.normal);
                                    vec2D colpt;
                                    vec2D colnorm;
                                    vec2D entnextpos = rigid1.GetNextPos();
                                    float coltime;
                                    if (entityCollision::wallCollision(ent1, entnextpos, wall2, colpt, colnorm, coltime)) {
                                        vec2D reflectiondir;
                                        entityCollision::wallBounce(colpt, colnorm, entnextpos, reflectiondir);
                                        rigid1.SetNextPos(entnextpos);
                                    }
                                }
                                else if (e2 == Col_Type::rect) {

                                    if (entityCollision::boundingBoxCircle(ent1, rigid2.GetMax(), rigid2.GetMin())) {
                                        //hit detected. take damage
                                    }
                                }
                            }
                            else if (e1 == Col_Type::line) {
                                if (e2 == Col_Type::circle) {
                                    wall wall2;
                                    wall2.p0 = rigid1.GetMin();
                                    wall2.p1 = rigid1.GetMax();
                                    vec2D temp = wall2.p1 - wall2.p0;
                                    wall2.normal.value.x = temp.value.y;
                                    wall2.normal.value.y = -temp.value.x;
                                    Normalize(wall2.normal, wall2.normal);
                                    circle_bound ent1;
                                    ent1.center = ent2pos;
                                    ent1.radius = rigid2.GetMax().value.x - ent2pos.value.x;
                                    vec2D colpt;
                                    vec2D colnorm;
                                    vec2D entnextpos = rigid2.GetNextPos();
                                    float coltime;
                                    if (entityCollision::wallCollision(ent1, const vec2D entnextpos, wall2, colpt, colnorm, coltime)) {
                                        vec2D reflectiondir;
                                        entityCollision::wallBounce(colpt, colnorm, vec2D entnextpos, vec2D &reflectiondir);
                                        rigid2.SetNextPos(entnextpos);
                                    }
                                }
                            }
                            else if (e1 == Col_Type::rect) {
                                if (e2 == Col_Type::circle) {
                                    circle_bound ent1;
                                    ent1.center = ent2pos;
                                    ent1.radius = rigid2.GetMax().value.x - ent2pos.value.x;
                                    if (entityCollision::boundingBoxCircle(ent1, rigid1.GetMax(), rigid1.GetMin())) {
                                        //hit detected. take damage
                                    }
                                }
                                else if (e2 == Col_Type::rect) {
                                    if (bool boundingBoxCollision(rigid1.GetMax(), rigid1.GetMin(), vec2D vel1, rigid2.GetMax(), rigid2.GetMin(), vec2D vel2, dt)) {
                                        //parry mechanics? 
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
	void CollisionSystem::End() {
        //remove all entities from array
    }
}
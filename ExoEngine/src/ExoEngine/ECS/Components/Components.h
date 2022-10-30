/*!*************************************************************************
****
\file Components.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/09/2022
\brief  This file contains all the Various Components to be used in the ECS
in the future. Currently, Every Component is still handling its own data
by inheriting from an abstract class of the JSONSerializer to serialize and
deserialize its data

****************************************************************************
***/
#pragma once
#include "Transform.h"
#include "RigidBody.h"
#include "WinData.h"
#include "Collider.h"
#include "NameTag.h"
#include "Sprite.h"

#define TransformComponent EM::Transform::Transform()
#define RigidBodyComponent EM::RigidBody::RigidBody()
#define ColliderComponent EM::Collider::Collider()
#define NameTagComponent EM::NameTag::NameTag()
#define SpriteComponent EM::Sprite::Sprite()

namespace EM
{

	//Logic Component

	//Enum Class Col_Type
	//AABB
	//Circle
	//Half - Extend
	//class Collider : public IComponent
	//{
	//public:
	//	Collider();
	//	~Collider() = default;
	//	virtual bool Deserialize(const rapidjson::Value& obj);
	//	virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
	//private:
	//	Col_Type mCol;
	//	vec2D mMin;
	//	vec2D mMax;
	//	float radius;
	//};

	//RigidBody Component
	//Velocity
	//Direction
	//Friction
	//Restitution

	//std::array of scripts
		//Array Name of Script std::string
		//Pointer to instance to the script (Depend on Script)
		//
		//Method 2 array of class logic component inside name and pointer to instance


	//Class of BaseScript
		//private member of entityID
		//GetComponent
	
	//PlayerMovement
	//Enemy Movement
	// 
	//Inherited class Script
		//Start
		//Update
		//End

	//LogicSystem
		//Update
		//Loop through entity
		//Loop through scripts in the component and call update
}
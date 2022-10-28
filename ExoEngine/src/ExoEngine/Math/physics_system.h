#pragma once
#include "RigidBody.h"
#include "physics.h"
#include "transformation.h"
//#include "../ECS/ECS.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
	class EM_API PhysicsSystem : System
	{
	public:
		virtual void Init() override;

		virtual void Update(float dt);
	private:
        //function take in acceleration, calculate and set force
       //function take force and find the acceleration of the moving object
        void calculate_accel(RigidBody2 obj);
        
       

         //reset function
        void reset_force(RigidBody2 obj);
        void reset_accel(RigidBody2 obj);
        void reset_velocity(RigidBody2 obj);
        void multiply_scale(Transform2 obj, vec2D Scale);
       
	};

}

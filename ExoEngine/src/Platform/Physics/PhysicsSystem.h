#pragma once
#include "Physics.h"
#include "ExoEngine/ECS/Components.h"
#include "empch.h"
#include "../../Platform/System/System.h"

namespace EM {
<<<<<<<< HEAD:ExoEngine/src/ExoEngine/Math/PhysicsSystem.h
	class PhysicsSystem : public System
	{
	public:
		virtual std::string GetName() { return "Update Positions"; }
		virtual void Init() override;

		virtual void Update();

		void End();
	private:
        //function take in acceleration, calculate and set force
       //function take force and find the acceleration of the moving object
        /*void calculate_accel(RigidBody2 obj);
        
       
========
    class PhysicsSystem : public System
    {
    public:
        virtual std::string GetName() { return "Physics"; }
        virtual void Init() override;

        virtual void Update();

        void End();
    private:
        //function take in acceleration, calculate and set force
       //function take force and find the acceleration of the moving object
        /*void calculate_accel(RigidBody2 obj);


>>>>>>>> a2c28223adcbb8c8baa1c79e249d860e41369b43:ExoEngine/src/Platform/Physics/PhysicsSystem.h

         //reset function
        void reset_force(RigidBody2 obj);
        void reset_accel(RigidBody2 obj);
        void reset_velocity(RigidBody2 obj);
        void multiply_scale(Transform2 obj, vec2D Scale);*/
<<<<<<<< HEAD:ExoEngine/src/ExoEngine/Math/PhysicsSystem.h
	};
========
    };
>>>>>>>> a2c28223adcbb8c8baa1c79e249d860e41369b43:ExoEngine/src/Platform/Physics/PhysicsSystem.h

}
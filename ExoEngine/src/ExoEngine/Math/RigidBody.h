#pragma once

#include "empch.h"
#include "Vmath.h"
#include "physics.h"
#include "ExoEngine/ECS/Components.h"

namespace EM
{

    
    struct RigidBody2 {    
        Col_Type Type;
        vec2D pos;//position of actor this is a temp object, to be deletedd after intergration
        float  mass;//nass of actor
        vec2D velocity{0,0};//speed of actor
        vec2D aceleration;//acceleration of actor
        vec2D force;//force applied
        bool mordify;

        aabb bounding_box;
        circle_bound bounding_circle;

        


        
    };


     /* //function take in acceleration, calculate and set force
        //function take force and find the acceleration of the moving object
        void calculate_accel();
       // void update_physics();
        //bounding box creation tool
        void set_aabb(aabb box);// create aabb

        //getter function
        vec2D get_accel();//return acceleration
        vec2D get_vel();//return velocity
        vec2D get_force();
        float get_rad();

        //reset function
        void reset_force();
        void reset_accel();
        void reset_velocity();

        //helper function and setter
        void set_weight(float Mass = { 0 });
        void set_velocity(vec2D Velocity);
        void set_acceleration(vec2D Accel);
        void set_pos(vec2D Pos);
        void set_Rad(float radius);
        
       
        
        //modifier 
        void add_weight(float Mass = {0});
        void add_Force(vec2D force = {0,0});
        void add_acceleration(vec2D Accel = {0,0});*/

}
#pragma onc

#include "empch.h"
#include "Vmath.h"
#include "physics.h"

namespace EM
{

    enum Col_Type
    {
        rectangle,
        Circle
    };
    
    class RigidBody2 {
    public:

        RigidBody2();
        RigidBody2(vec2D vel = {0,0});

        //function take in acceleration, calculate and set force
        //function take force and find the acceleration of the moving object
        void calculate_accel();
       // void update_physics();
        //bounding box creation tool
        void set_aabb(aabb box);// create aabb

        //getter function
        vec2D get_accel();//return acceleration
        vec2D get_vel();//return velocity
        vec2D get_force();

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
        void add_Force(Vec2 force = {0,0});
        void add_acceleration(Vec2 Accel = {0,0});




    private:
        Col_Type Type;
        Vec2 pos;//position of actor this is a temp object, to be deletedd after intergration

        float  mass;//nass of actor
        Vec2 velocity{0,0};//speed of actor
        Vec2 aceleration;//acceleration of actor
        Vec2 force;//force applied
        bool mordify;

        aabb bounding_box;
        circle bounding_circle;




        
    };


}
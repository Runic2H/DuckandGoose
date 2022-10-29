#pragma once
#include "ExoEngine/Math/Vmath.h"
#include "IComponent.h"

namespace EM
{
	enum class Col_Type
	{
		none,
		circle, //-------Circle
		line, //---------LineSegment
		rect //----------AABB
	};

	class RigidBody : public IComponent
	{
	public:
		RigidBody();
		~RigidBody() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		vec2D& GetMin() { return min; }
		vec2D& GetMax() { return max; }
		vec2D& GetVel() { return vel; }
		vec2D& GetInitVel() { return initvel; }
		vec2D& GetNextPos() { return nextpos; }
		Col_Type& GetCollider() { return collider; }

		void SetMin(vec2D Min) { min = Min; }
		void SetMax(vec2D Max) { max = Max; }
		void SetVel(vec2D Vel) { vel = Vel; }
		void SetInitVel(vec2D Vel) { initvel = Vel; }
		void SetNextPos(vec2D Pos) { nextpos = Pos; }
		void SetCollider(Col_Type col) { collider = col; }

		virtual std::string GetComponentName();

	private:
		vec2D		min;
		vec2D		max;
		vec2D		vel;
		vec2D		initvel;
		vec2D		nextpos; //set to position + vel. for use in collision response calculation
		Col_Type 	collider;
	};
}
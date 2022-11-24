#pragma once
#include "IComponent.h"
#include "ExoEngine/Math/Vmath.h"

namespace EM
{

	class Collider : public IComponent
	{
	public:
		enum class ColliderType
		{
			none,
			circle, //-------Circle
			line, //---------LineSegment
			rect, //----------AABB
			button
		};
		Collider();
		~Collider() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void SetCollider(ColliderType type) { mCol = type; }
		void SetCollider(int type) 
		{
			if (static_cast<ColliderType>(type) < ColliderType::none || static_cast<ColliderType>(type) > ColliderType::button)
			{
				assert("Not a Valid Collider");
			}
			mCol = static_cast<ColliderType>(type);
		}
		void SetOffset(vec2D input) { offset = input; }
		void SetMin(vec2D input) { mMin = input; }
		void SetMax(vec2D input) { mMax = input; }
		void SetRad(float input) { mRadius = input; }
		void SetHit(int input) { hit = input; }
		void SetNormal(vec2D input) { CollisionNormal = input; }
		void ToggleAlive() { mAlive = mAlive ? false : true; }

		ColliderType& GetCollider() { return mCol; }
		vec2D GetOffset() { return offset; }
		vec2D GetMin() { return mMin; }
		vec2D GetMax() { return mMax; }
		float GetRad() { return mRadius; }
		int GetHit() { return hit; }
		vec2D GetNormal() { return CollisionNormal; }
		bool GetAlive() { return mAlive; }

	private:
		ColliderType mCol{};
		vec2D CollisionNormal;
		vec2D mMin;
		vec2D mMax;
		vec2D offset;
		int hit;
		float mRadius;
		bool mAlive;
	};
}
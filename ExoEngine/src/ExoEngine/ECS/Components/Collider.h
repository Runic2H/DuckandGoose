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
			rect //----------AABB
		};
		Collider();
		~Collider() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		void SetCollider(ColliderType type) { mCol = type; }
		void SetCollider(int type) 
		{
			if (static_cast<ColliderType>(type) < ColliderType::none || static_cast<ColliderType>(type) > ColliderType::rect)
			{
				assert("Not a Valid Collider");
			}
			mCol = static_cast<ColliderType>(type);
		}
	private:
		ColliderType mCol{};
		vec2D mMin;
		vec2D mMax;
		float mRadius;
	};
}
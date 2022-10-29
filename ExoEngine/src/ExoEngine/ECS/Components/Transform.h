#pragma once
#include "ExoEngine/Math/Vmath.h"
#include "IComponent.h"

namespace EM
{
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		vec2D& GetPos() { return position; }
		vec2D& GetScale() { return scale; }
		float& GetRot() { return rot; }

		void SetPos(vec2D Pos) { position = Pos; }
		void SetScale(vec2D Scale) { scale = Scale; }
		void SetRot(float value) { rot = value; }

		virtual std::string GetComponentName();


	private:
		vec2D position;
		vec2D scale;
		float rot;
	};
}
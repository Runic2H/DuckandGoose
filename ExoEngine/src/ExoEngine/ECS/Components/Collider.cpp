#include "Collider.h"

namespace EM
{
	Collider::Collider() : mCol{ColliderType::none}, mMin{vec2D()}, mMax{vec2D()}, mRadius{0.3f}, hit{0} {}

	bool Collider::Deserialize(const rapidjson::Value& obj)
	{
		mCol = static_cast<ColliderType>(obj["ColliderType"].GetInt());
		mMin = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
		mMax = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());
		offset = vec2D(obj["offsetX"].GetFloat(), obj["offsetY"].GetFloat());
		mRadius = obj["radius"].GetFloat();
		return true;
	}

	bool Collider::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("ColliderType");
		writer->Int(static_cast<int>(mCol));
		writer->Key("minX");
		writer->Double(mMin.x);
		writer->Key("minY");
		writer->Double(mMin.y);
		writer->Key("maxX");
		writer->Double(mMax.x);
		writer->Key("maxY");
		writer->Double(mMax.y);
		writer->Key("offsetX");
		writer->Double(offset.x);
		writer->Key("offsetY");
		writer->Double(offset.y);
		writer->Key("radius");
		writer->Double(mRadius);
		writer->EndObject();
		return true;
	}
}
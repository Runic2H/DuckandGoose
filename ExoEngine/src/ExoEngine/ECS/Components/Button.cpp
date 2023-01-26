#include "empch.h"
#include "Button.h"

EM::Button::Button()
{
}

bool EM::Button::Deserialize(const rapidjson::Value& obj)
{
	//mMin = vec2D(obj["minX"].GetFloat(), obj["minY"].GetFloat());
	//mMax = vec2D(obj["maxX"].GetFloat(), obj["maxY"].GetFloat());

	selected = obj["selected"].GetBool();
	clicked = obj["clicked"].GetBool();
	return true;
}

bool EM::Button::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
{	
		
	writer->StartObject();
	writer->Key("selected");
	writer->Bool(selected);
	writer->Key("clicked");
	writer->Bool(clicked);
	writer->EndObject();
	return true;
}

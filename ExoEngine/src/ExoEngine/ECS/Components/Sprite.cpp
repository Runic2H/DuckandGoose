#include "empch.h"
#include "Sprite.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	Sprite::Sprite() : color(1.0f, 1.0f, 0.0f, 1.0f), m_texturename("Blank")
	{
	}
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{
		color = glm::vec4(obj["R"].GetFloat(), obj["G"].GetFloat(),
			obj["B"].GetFloat(), obj["A"].GetFloat());
		m_texturename = std::string(obj["TextureName"].GetString());
		return true;
	}
	bool Sprite::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("R");
		writer->Double(color.x);
		writer->Key("G");
		writer->Double(color.y);
		writer->Key("B");
		writer->Double(color.z);
		writer->Key("A");
		writer->Double(color.w);
		writer->Key("TextureName");
		writer->String(m_texturename.c_str());
		writer->EndObject();
		return true;
	}
	std::string Sprite::GetComponentName()
	{
		std::string className = __FUNCTION__;
		size_t found = className.find_last_of("::") - 1;
		className = className.substr(0, found);
		found = className.find_last_of("::") + 1;
		className = className.substr(found);
		return className;
	}
	
}
#include "empch.h"
#include "Sprite.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
namespace EM {
	Sprite::Sprite() : m_texturename("Blank")
	{
	}
	bool Sprite::Deserialize(const rapidjson::Value& obj)
	{

		m_texturename = std::string(obj["TextureName"].GetString());
		return true;
	}
	bool Sprite::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("TextureName");
		writer->String(m_texturename.c_str());
		writer->EndObject();
		return true;
	}
	
	
}
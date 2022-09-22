#include "JSONserialization.h"

namespace BaseEngine
{
	std::string BaseEngine::JSONSerializer::Serialize() const
	{
		rapidjson::StringBuffer ss;
		rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
		if (Serialize(&writer)) 
		{ 
			return ss.GetString(); 
		}
		return "";
	}

	bool BaseEngine::JSONSerializer::Deserialize(const std::string& stringbuffer)
	{
		rapidjson::Document doc;
		doc.Parse(stringbuffer.c_str());
		if (!InitDocument(stringbuffer, doc))
		{
			return false;
		}
		else
		{
			Deserialize(doc);
		}
		return true;
	}

	bool BaseEngine::JSONSerializer::DeserializeFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		ifs.close();

		return Deserialize(buffer.str());
	}

	bool BaseEngine::JSONSerializer::SerializeToFile(const std::string& filePath)
	{
		std::ofstream ofs(filePath);
		std::string str = Serialize();
		ofs << str;
		ofs.flush();
		ofs.close();

		return true;
	}

	bool BaseEngine::JSONSerializer::InitDocument(const std::string& stringbuffer, rapidjson::Document& doc)
	{
		if (stringbuffer.empty())
			return false;

		std::string validJson(stringbuffer);

		return !doc.Parse(validJson.c_str()).HasParseError() ? true : false;
	}

	Player::Player() : _name{ "Player" }, _health{ 0 }, _armour{ 0 } {};

	Player::~Player() {};

	bool BaseEngine::Player::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->String("name"); // create Id property
		writer->String(_name.c_str());  // write the Id value from the object instance

		writer->String("health");
		writer->Int(_health);

		writer->String("armour");
		writer->Double(_armour);

		writer->EndObject();

		return true;
	}

	bool BaseEngine::Player::Deserialize(const rapidjson::Value& obj)
	{
		Name(obj["name"].GetString());
		Health(obj["health"].GetInt());
		Armour(obj["armour"].GetDouble());
		return true;
	}
}
#include "WinData.h"

namespace EM
{
	//Window
	WinData::WinData() : title{ "Exomata" }, width{ 0 }, height(0), currentWidth{ 0 }, currentHeight{ 0 }
	{
		//WinData::SerializeToFile("Window.json");
	};
	bool WinData::Deserialize(const rapidjson::Value& obj)
	{
		title = obj["Title"].GetString();
		width = obj["Width"].GetUint();
		height = obj["Height"].GetUint();
		currentWidth = obj["Cwidth"].GetUint();
		currentHeight = obj["Cheight"].GetUint();
		return true;
	}
	bool WinData::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();
		writer->Key("Title");
		writer->String(title.c_str());
		writer->Key("Width");
		writer->Uint(width);
		writer->Key("Height");
		writer->Uint(height);
		writer->Key("Cwidth");
		writer->Uint(currentWidth);
		writer->Key("Cheight");
		writer->Uint(currentHeight);
		writer->EndObject();
		return true;
	}

	std::string WinData::GetComponentName()
	{
		std::string className = __FUNCTION__;
		size_t found = className.find_last_of("::") - 1;
		className = className.substr(0, found);
		found = className.find_last_of("::") + 1;
		className = className.substr(found);
		return className;
	}
}
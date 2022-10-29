#pragma once
#include "IComponent.h"
#include "empch.h"

namespace EM
{
	//Window Component
	class WinData : public IComponent
	{
	public:
		WinData();
		~WinData() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		std::string GetTitle() { return title; }
		unsigned int GetWidth() { return width; }
		unsigned int GetHeight() { return height; }
		unsigned int GetCurrWidth() { return currentWidth; }
		unsigned int GetCurrHeight() { return currentHeight; }

		void SetTitle(std::string Title) { title = Title; }
		void SetWidth(unsigned int Width) { width = Width; }
		void SetHeight(unsigned int Height) { height = Height; }
		void SetCurrWidth(unsigned int CurrWidth) { currentWidth = CurrWidth; }
		void SetCurrHeight(unsigned int CurrHeight) { currentHeight = CurrHeight; }

		virtual std::string GetComponentName();


	private:
		std::string title;
		unsigned int width,
			height,
			currentWidth,
			currentHeight;
	};
}
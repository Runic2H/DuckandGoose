#pragma once
#include "IComponent.h"
#include "glm/glm.hpp"
#include "Platform/Graphics/Texture.h"
namespace EM {

	class Sprite : public IComponent
	{
	public:
		Sprite();
		~Sprite() = default;
		virtual bool Deserialize(const rapidjson::Value & obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>*writer) const;

		void SetTexture(const std::string& name) { m_texturename = name; }
		std::string& GetTexture() { return m_texturename; }

		void SetColor(glm::vec4 mColor) { color = mColor; }
		glm::vec4& GetColor() { return color; }
		//boolean isanimated
		//texture index 
		//altas 

		virtual std::string GetComponentName();
	private:
		//for now using glm math library as we dont have vec4 
		glm::vec4 color;
		std::string m_texturename;
	};
}
/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-2-2022
\brief			This file contain the defintion for ResourceManager class.
				For now it can only load textures and shader.
****************************************************************************
***/
#include "empch.h"
#include "ResourceManager.h"

namespace EM {
	std::map <std::string, std::shared_ptr<Texture>> ResourceManager::textures;
	std::map <std::string, std::shared_ptr<Shader>> ResourceManager::shaders;
	std::map <std::string, std::shared_ptr<CAudioEngine>> ResourceManager::audios;
	std::map <std::string, std::shared_ptr<Texture>> ResourceManager::Icons;
	//TODO to load different fonts and maybe audio/music
	//std::map <std::string, std::shared_ptr<Font>> ResourceManager::fonts;
	std::shared_ptr<Texture> ResourceManager::LoadTexture(std::string name, const std::string& filepath)
	{
		return textures[name] = ResourceManager::LoadTextureFromFile(filepath);
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(std::string name)
	{
		return textures[name];
	}

	std::shared_ptr<Texture> ResourceManager::LoadTextureFromFile(const std::string& filepath)
	{
		auto m_texture = std::make_shared<Texture>();
		m_texture->GenTexture(filepath);
		return m_texture;
	}

	std::shared_ptr<Texture> ResourceManager::GenTexture(unsigned int width, unsigned int height)
	{
		auto m_texture = std::make_shared<Texture>();
		m_texture->GenTexture(width, height);
		return m_texture;
	}

	std::shared_ptr<Texture> ResourceManager::LoadIcons(std::string name, const std::string& filepath)
	{

		return Icons[name] = ResourceManager::LoadIconsFromFile(filepath);
	}

	std::shared_ptr<Texture> ResourceManager::GetIcon(std::string name)
	{
		return Icons[name];
	}

	std::shared_ptr<Shader> ResourceManager::LoadShaderFromFile(const std::string& filepath)
	{
		auto m_shader = std::make_shared<Shader>(filepath);
		
		return m_shader;
	}

	std::shared_ptr<Shader> ResourceManager::LoadShader(std::string name, const std::string& filepath)
	{
		return shaders[name] = ResourceManager::LoadShaderFromFile(filepath);
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(std::string name)
	{
		return shaders[name];
	}


	std::shared_ptr<Font> ResourceManager::LoadFontFromFile(const std::string& filepath, unsigned int fontsize)
	{
		auto m_font = std::make_shared<Font>();
		m_font->Load(filepath, fontsize);
		return m_font;
	}

	std::shared_ptr<Texture> ResourceManager::LoadIconsFromFile(const std::string& filepath)
	{
		auto mIcons = std::make_shared<Texture>();
		mIcons->GenTexture(filepath);
		return mIcons;
	}

	std::shared_ptr<CAudioEngine> ResourceManager::LoadAudioFromFile(const std::string& filepath)
	{
		auto m_audio = std::make_shared<CAudioEngine>();
		m_audio->Loadsound(filepath);
		return m_audio;
	}

	std::shared_ptr<CAudioEngine> ResourceManager::GetAudio(std::string name)
	{
		return audios[name];
	}

	std::shared_ptr<CAudioEngine> ResourceManager::LoadAudio(std::string name, const std::string& filepath)
	{
		(void)filepath; //TODO removed when proper resourcemanager for audio
		return std::shared_ptr<CAudioEngine>();
	}

	//TO be implement
	// 
	//std::shared_ptr<Font> ResourceManager::LoadFont(std::string name, unsigned int size)
	//{
	//	return std::shared_ptr<Font>();
	//}
	//std::shared_ptr<Font> ResourceManager::GetFont(std::string name)
	//{
	//	return std::shared_ptr<Font>();
	//}

	void EM::ResourceManager::clear()
	{
		/*for (auto iter : textures)
		{
			iter.second->~Texture();
		}

		for (auto iter : shaders)
			iter.second->~Shader();

		for (auto iter : Icons)
			iter.second->~Texture();*/
		textures.clear();
		Icons.clear();
		shaders.clear();
	}

	
}
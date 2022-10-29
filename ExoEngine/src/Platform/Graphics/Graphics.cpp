/*!*************************************************************************
****
\file			Graphic.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain a temporarily rendering class which will be bring over
				once render class is up.

****************************************************************************
***/
#include "empch.h"
#include "Graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/Timer/Time.h"


namespace EM {

	extern ECS ecs;

	void Graphic::LoadTexture(std::string filename)
	{
		std::ifstream ifs(filename.c_str());
		std::string name, textPath;
		while (ifs >> name >> textPath)
			ResourceManager::LoadTexture(name.c_str(), textPath.c_str());

		ifs.close();
	}

	//for testing purpose
	void Graphic::Init()
	{
		ResourceManager::LoadShader("QuadShader", "Assets/Shaders/texture.shader");
		ResourceManager::LoadShader("LineShader", "Assets/Shaders/Line.shader");
		ResourceManager::LoadShader("CircleShader", "Assets/Shaders/Circle.shader");
		
		LoadTexture("Assets/textures.txt");
		Renderer::Init();
		m_Font->Init();
	}


	void Graphic::Update(float frametime)
	{
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		m_Renderer->ResetInfo();
		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);// begin of the renderer 
		//test for rendering texture, line and rectange to be removed
		 
		for (auto const& entity : mEntities)
		{
			auto& transform = ecs.GetComponent<Transform>(entity);
			auto& sprite = ecs.GetComponent<Sprite>(entity);
			index1 = SpriteRender::CreateSprite(GETTEXTURE(sprite.GetTexture().c_str()), { 0.f,0.f });
			m_Renderer->DrawSprite({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y },
				index1);
	
		}
		
		
		m_Renderer->End(); //when flush happened
		//for testing 
		camera.SetPosition({ m_cameraposition.x, m_cameraposition.y, 0.0f });

		if (p_Input->isKeyPressed(GLFW_KEY_W))
			m_cameraposition.y += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_S))
			m_cameraposition.y -= CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_D))
			m_cameraposition.x += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_A))
		{
			m_cameraposition.x -= CameraSpeed * frametime;
		}
		camera.MouseScrolling();
		
		Timer::GetInstance().Update(Systems::GRAPHIC);
	}
	void Graphic::End()
	{
		ResourceManager::clear();
		Renderer::ShutDown();
	}

}
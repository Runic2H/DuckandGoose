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

	//for testing purpose
	void Graphic::Init()
	{
		ResourceManager::LoadShader("QuadShader", "Assets/Shaders/texture.shader");
		ResourceManager::LoadShader("LineShader", "Assets/Shaders/Line.shader");
		
		ResourceManager::LoadTexture("BackGround", "Assets/Textures/BackGround.png");
		ResourceManager::LoadTexture("Player", "Assets/Textures/PlayerSpriteSheet.png");
		ResourceManager::LoadTexture("Splash", "Assets/Textures/HitSplash.png");

		Renderer::Init();
		m_Font->Init();
	}


	void Graphic::Update(float frametime)
	{
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);
		{//test for rendering texture, line and rectange to be removed
			m_Font->RenderText("Duck and Goose! Quack", 0.0f, 0.0f, 0.01f, camera, { 1.0f, -0.5f, 0.8f });

		}
		for (auto const& entity : mEntities)
		{
			auto& transform = ecs.GetComponent<Transform>(entity);
			m_Renderer->DrawQuad({ transform.GetPos().value.x , transform.GetPos().value.y }, { transform.GetScale().value.x , transform.GetScale().value.y }, transform.GetRot(), { 1.0f, -0.5f, 0.8f, 1.0f });
		}
		
		m_Renderer->End();
		//for testing 
		camera.SetPosition(m_cameraposition);

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
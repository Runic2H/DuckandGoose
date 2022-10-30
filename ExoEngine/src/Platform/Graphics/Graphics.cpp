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
		ResourceManager::LoadShader("CircleShader", "Assets/Shaders/Circle.shader");
		
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
		m_Renderer->ResetInfo();
		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);
		//test for rendering texture, line and rectange to be removed
		m_Font->RenderText("Duck and Goose! Quack", { 0.0f, 0.0f }, 0.005f, camera, { 1.0f, -0.5f, 0.8f });	
	
		for (auto const& entity : mEntities)
		{
			auto& transform = p_ecs.GetComponent<Transform>(entity);
			//draw quad without texture
			m_Renderer->DrawQuad({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y }, transform.GetRot(), {1.0f,0.0f,0.0f,1.0f});
			
		}

		m_Renderer->End();
		//for testing 
		camera.SetPosition({ player.position.x, player.position.y, 0.0f });

		if (p_Input->isKeyPressed(GLFW_KEY_W))
			player.position.y += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_S))
			player.position.y -= CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_D))
			player.position.x += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_A))
		{
			player.position.x -= CameraSpeed * frametime;
			
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
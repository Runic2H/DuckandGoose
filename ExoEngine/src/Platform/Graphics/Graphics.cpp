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
		ResourceManager::LoadShader("BasicShader","Assets/Shaders/basic.shader");
		ResourceManager::LoadShader("TextureShader", "Assets/Shaders/texture.shader");
		ResourceManager::LoadShader("LineShader", "Assets/Shaders/Line.shader");
		ResourceManager::LoadTexture("Duck","Assets/Textures/DuckandGoose.png");
		ResourceManager::LoadTexture("BackGround", "Assets/Textures/BackGround.png");
		ResourceManager::LoadTexture("Player", "Assets/Textures/PlayerSpriteSheet.png");
		m_Renderer->Init();
	}


	void Graphic::Update(float frametime)
	{
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);

		m_Renderer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);


		//example for setting position to a square
		glm::vec4 redcolor{ 1.0f, 0.0f, 0.0f, 1.0f };
		glm::vec4 greencolor{ 0.0f, 1.0f, 0.0f, 1.0f };

		for (auto const& entity : mEntities)
		{
			auto& transform = ecs.GetComponent<Transform>(entity);
			m_Renderer->DrawQuad({ transform.GetPos().value.x , transform.GetPos().value.y }, { transform.GetScale().value.x , transform.GetScale().value.y }, transform.GetRot(), greencolor);
		}

		//static float rotationspeed = 0.0f;
		//rotationspeed += frametime * 10.0f;

		//static float rotationspeed2 = 0.0f;
		//rotationspeed2 -= frametime * 10.0f;
		////test for box with color and without texture
		//glm::vec2 pos{ 2.0f };
		//m_Renderer->DrawQuad(pos, { 1.0f, 1.0f }, redcolor);

		//glm::vec2 pos1{ 0.0f };
		//
		//m_Renderer->DrawQuad(pos1, { 1.0f, 1.0f }, rotationspeed, greencolor);
		//
		//glm::vec2 pos2{ -1.0f };
		//m_Renderer->DrawQuad(pos2, { 2.5f, 1.0f }, ResourceManager::GetTexture("BackGround"));
		//
		//glm::vec2 pos3{ -1.0f, 1.0f };
		//m_Renderer->DrawQuad(pos3, { 1.0f, 1.0f }, ResourceManager::GetTexture("Duck"));

		//glm::vec2 pos4{ 1.0f, -1.0f };
		//m_Renderer->DrawQuad(pos4, { 1.0f, 1.0f }, rotationspeed2, ResourceManager::GetTexture("Duck"));

		////example for renderering tile once data is up
		//for (int y = 0; y < 30 ; y++)
		//{
		//	for (int x = 0; x < 30; x++)
		//	{
		//		glm::vec2 tilePos(x * 0.11f, y * 0.11f);
		//		m_Renderer->DrawQuad(tilePos, { 0.1f, 0.1f }, ResourceManager::GetTexture("Player"));
		//	}
		//}
		/*glm::vec3 pos5{ 0.0f, 0.0f, 0.0f };
		glm::vec3 pos6{ 0.5f, 0.5f, 0.0f };
		m_Renderer->DrawLine(pos5, pos6, { 1.0f, 0.1f, 0.1f, 1.0f });

		glm::vec3 pos3{ 1.0f ,1.0f, 0.0f};

		m_Renderer->DrawRect(pos3, { 0.1f, 0.1f }, { 0.0f, 0.1f, 1.0f, 1.0f });*/
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
		Renderer::End();
	}
}
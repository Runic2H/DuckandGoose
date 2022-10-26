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
		//m_Font->RenderText("Duck and Goose! Quack", { 0.0f, 0.0f }, 0.005f, camera, { 1.0f, -0.5f, 0.8f });
		
			
	
		for (auto const& entity : mEntities)
		{
			auto& transform = ecs.GetComponent<Transform>(entity);
			//draw quad without texture
			m_Renderer->DrawQuad({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y }, transform.GetRot(), { 1.0f, -0.5f, 0.8f, 1.0f });
			
		}

		// draw quad with texture
		m_Renderer->DrawQuad({ 0.0f, -0.5f }, { 1.0f, 1.0f }, ResourceManager::GetTexture("BackGround"));
		// draw line with color
		m_Renderer->DrawLine({ 0.0f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		// draw rect with color
		m_Renderer->DrawRect({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		
		//render circle
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.0, 0.0f, 0.0f }) //position of the circle
								*glm::scale(glm::mat4(1.0f), glm::vec3(0.5*2)); //radius * 2
		m_Renderer->DrawCircle(transform, { 0.0f, 1.0f, 0.0f, 1.0f }, 0.01f);

		glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), { 1.0, 1.0f, 0.0f }) //position of the circle
			* glm::scale(glm::mat4(1.0f), glm::vec3(0.5 * 2)); //radius * 2
		m_Renderer->DrawCircle(transform2, { 0.0f, 0.0f, 1.0f, 1.0f }); //depth is defaulted as 1.0f so i a full circle no hollow

		/*custom matrix test here*/
		Mat4x4 testform{ 1.0f };
		Mat4x4 scale{ 1.0f };
		Mat4x4 translate{ 1.0f };
		Mat4x4 rotate{ 1.0f };
		Translate4x4(translate, 0.0f, 0.0f, 0.0f);
		Scale4x4(scale, 0.2f, 0.2f, 0.0f);
		RotRad4x4(rotate, 45, Vec3{ 0.0f,0.0f,1.0f });
		testform = translate * (scale * rotate);
		//m_Renderer->DrawQuad(mtx_adapter(testform), { 0.0f,1.0f,0.0f, 1.0f });
		/*custom matrix test here*/

		m_Renderer->End();
		//for testing 
		
		//camera.SetPosition({.GetPos().x, .GetPos().y, 0.0f });
		/*if (p_Input->isKeyPressed(GLFW_KEY_W))
			player.position.y += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_S))
			player.position.y -= CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_D))
			player.position.x += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_A))
		{
			player.position.x -= CameraSpeed * frametime;
			
		}*/
		camera.MouseScrolling();
		
		Timer::GetInstance().Update(Systems::GRAPHIC);
	}
	void Graphic::End()
	{
		ResourceManager::clear();
		Renderer::ShutDown();
	}
}
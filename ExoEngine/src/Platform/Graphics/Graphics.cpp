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
#include "Platform/LevelEditor/LevelEditor.h"
#include "ExoEngine/Math/Math.h"


namespace EM {

	//extern ECS ecs;

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
		(void)frametime;
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		m_Renderer->ResetInfo();
		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);// begin of the renderer 
		
		m_Renderer->DrawQuad({ 0.0f, 0.0f }, { 10.0f, 4.0f, }, GETTEXTURE("BackGround"));
			
	
		for (auto const& entity : mEntities)
		{
			auto& transform = p_ecs.GetComponent<Transform>(entity);
			auto& sprite = p_ecs.GetComponent<Sprite>(entity);
			auto& velocity = p_ecs.GetComponent<RigidBody>(entity);
			auto& collider = p_ecs.GetComponent<Collider>(entity);
			index1 = SpriteRender::CreateSprite(GETTEXTURE(sprite.GetTexture()), { sprite.GetIndex().x, sprite.GetIndex().y });
			m_Renderer->DrawSprite({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y },
				transform.GetRot(), index1);
			if (p_Editor->mDebugDraw)
			{
				if(p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::rect))
					m_Renderer->DrawRect({ transform.GetPos().x , transform.GetPos().y, 0.0f }, { transform.GetScale().x , transform.GetScale().y },
					{1.0f, 0.0f, 0.0f,1.0f});
				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::line))
					m_Renderer->DrawLine({ transform.GetPos().x, transform.GetPos().y, 0.0f },
						{(transform.GetPos().x + (25*velocity.GetVel().x)), (transform.GetPos().y + (25*velocity.GetVel().y)),0.0f },
						{ 0.0f, 1.0f, 0.0f, 1.0f });
				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::circle))
				{
					glm::mat4 Transform = glm::translate(glm::mat4(1.0f), { transform.GetPos().x , transform.GetPos().y, 0.0f })*
							glm::scale(glm::mat4(1.0f), glm::vec3(collider.GetRad() * 2));
					m_Renderer->DrawCircle(Transform, { 0.5f,0.4f,1.0f, 1.0f }, 0.01f);
				}
			}
		}

		m_Renderer->End();
		//m_Font->RenderText("Duck and Goose! Quack", { 0.0f, 0.0f }, 0.005f, camera, { 1.0f, -0.5f, 0.8f });
		 
		//for debug purpose 
		for (auto const& entity : mEntities)
		{
			if (p_ecs.HaveComponent<Player>(entity))
				camera.SetPosition({ p_ecs.GetComponent<Transform>(entity).GetPos().x,
					p_ecs.GetComponent<Transform>(entity).GetPos().y,
					0.0f });
		}
		/*if (p_Input->isKeyPressed(GLFW_KEY_W))
			player.position.y += CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_S))
			m_cameraposition.y -= CameraSpeed * frametime;
		if (p_Input->isKeyPressed(GLFW_KEY_D))
			m_cameraposition.x += CameraSpeed * frametime;
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
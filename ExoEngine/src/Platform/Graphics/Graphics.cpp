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
#include "ExoEngine/GUI/GUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/ResourceManager/ResourceManager.h"
#include "ExoEngine/Timer/Time.h"
#include "Platform/LevelEditor/LevelEditor.h"
#include "ExoEngine/Math/Math.h"
#include "FrameBuffer.h"
#include "ExoEngine/Timer/Fps.h"
namespace EM {

	//extern ECS ecs;

	void Graphic::LoadIconsTexture(std::string filename)
	{
		std::ifstream ifs(filename.c_str());
		std::string name, textPath;
		while (ifs >> name >> textPath)
			ResourceManager::LoadIcons(name.c_str(), textPath.c_str());

		ifs.close();
	}
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
		
	
		LoadIconsTexture("Assets/Text/Icons.txt");
		LoadTexture("Assets/Text/texture.txt");
		
		
		FrameBufferSpecification fbspec;
		fbspec.Attachments = { FrameBufferTextureFormat::RGBA8, FrameBufferTextureFormat::RED_INTEGER, FrameBufferTextureFormat::DEPTH };
		fbspec.Width = mwindow.GetWidth();
		fbspec.Height = mwindow.GetHeight();
		p_FrameBuffer->SetFrameBufferSpecification(fbspec);
		Renderer::Init();
		m_Font->Init();
	}


	void Graphic::Update(float frametime)
	{
		//(void)frametime;
		Timer::GetInstance().Start(Systems::GRAPHIC);
		Timer::GetInstance().GetDT(Systems::GRAPHIC);
		
		
		m_Renderer->ResetInfo();
		m_Renderer->Clear();
		p_FrameBuffer->Bind();
		glClearTexImage(p_FrameBuffer->GetColorAttachmentRendererID(1), 0, GL_RED_INTEGER, GL_INT, 0);

		m_Renderer->SetClearColor({ 0.0f, 0.1f, 0.1f, 1.0f });
		m_Renderer->Clear();
		m_Renderer->Begin(camera);// begin of the renderer 
		p_GUI->VPmat = camera.GetViewProjectionMatrix();
		

		m_Renderer->DrawQuad({ 0.0f, 0.0f }, { 10.0f, 4.0f, }, GETTEXTURE("BackGround"));

		for (auto const& entity : mEntities)
		{
			auto& transform = p_ecs.GetComponent<Transform>(entity);
			auto& sprite = p_ecs.GetComponent<Sprite>(entity);
			auto& velocity = p_ecs.GetComponent<RigidBody>(entity);
			auto& collider = p_ecs.GetComponent<Collider>(entity);
			if (sprite.mIsanimated)
			{
				animator.AddFrameInfo(p_ecs.GetComponent<Sprite>(entity));
				animator.UpdateAnimation(frametime);
			}
			if (sprite.mIsSpriteSheet)
			{
				index1 = SpriteRender::CreateSprite(GETTEXTURE(sprite.GetTexture()), { sprite.GetIndex().x, sprite.GetIndex().y });
				m_Renderer->DrawSprite({ transform.GetPos().x , transform.GetPos().y }, { transform.GetScale().x , transform.GetScale().y },
					transform.GetRot(), index1);
			}
			else
			{
				m_Renderer->DrawQuad({ transform.GetPos().x, transform.GetPos().y }, { transform.GetScale().x, transform.GetScale().y },
					GETTEXTURE(sprite.GetTexture()));
			}

			if (p_Editor->mDebugDraw)
			{
				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::rect))
					m_Renderer->DrawRect({ transform.GetPos().x , transform.GetPos().y, 0.0f }, { transform.GetScale().x , transform.GetScale().y },
						{ 1.0f, 0.0f, 0.0f,1.0f });

				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::line))
					m_Renderer->DrawLine({ transform.GetPos().x, transform.GetPos().y, 0.0f },
						{ (transform.GetPos().x + (25 * velocity.GetVel().x)), (transform.GetPos().y + (25 * velocity.GetVel().y)),0.0f },
						{ 0.0f, 1.0f, 0.0f, 1.0f });

				if (p_ecs.HaveComponent<Collider>(entity) && (p_ecs.GetComponent<Collider>(entity).GetCollider() == Collider::ColliderType::circle))
				{
					glm::mat4 Transform = glm::translate(glm::mat4(1.0f), { transform.GetPos().x , transform.GetPos().y, 0.0f }) *
						glm::scale(glm::mat4(1.0f), glm::vec3(collider.GetRad() * 2));
					m_Renderer->DrawCircle(Transform, { 0.5f,0.4f,1.0f, 1.0f }, 0.01f);
				}
			}
		}

		
		for (auto const& entity : mEntities)
		{
			if (p_ecs.HaveComponent<Tag>(entity) && std::strcmp(p_ecs.GetComponent<Tag>(entity).GetTag().c_str(),"Player"))
				camera.SetPosition({ p_ecs.GetComponent<Transform>(entity).GetPos().x,
					p_ecs.GetComponent<Transform>(entity).GetPos().y,
					0.0f });
		}
		
		if (p_GUI->check_pause() == true)
		{

			m_Renderer->DrawQuad({ camera.GetPosition().x + 0.0f, camera.GetPosition().y + 0.5f,0.0f }, { 1.0f, 0.2f }, { 0.3f, 0.4f, 0.5f, 1.0f });//to create the continue button
			p_GUI->set_continue_button({ 0.0f,0.5f }, 1.0f, 0.2f);//assign position and scale into the GUI
			m_Renderer->DrawQuad({ camera.GetPosition().x + 0.0f, camera.GetPosition().y - 0.0f,0.0f }, { 1.0f, 0.2f }, { 0.3f, 0.4f, 0.5f, 1.0f });//to create the quit button 
			p_GUI->set_pause_button({ 0.0f,0.0f }, 1.0f, 0.2f);//assign position and scale into the GUI

		}
		m_Renderer->End();
		p_FrameBuffer->UnBind();
		

		if (p_GUI->check_pause() == true)
		{
			m_Font->RenderText("Continue", { camera.GetPosition().x - 0.2f ,camera.GetPosition().y + 0.5f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//render the text for the continue button
			m_Font->RenderText("Quit", { camera.GetPosition().x - 0.1f ,camera.GetPosition().y + 0.0f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//render the text for the first button
			m_Font->RenderText("Game Paused", { camera.GetPosition().x - 0.32f , camera.GetPosition().y + 0.7f }, 0.002f, camera, { 1.0f, -0.5f, 1.0f });//to render text for the quit button
		}


		if (p_Input->isKeyPressed(GLFW_KEY_ESCAPE) && p_GUI->pause_switch == false)//toggle menu with escape
		{
			p_GUI->pause_switch = true;//set first boolean to true to prevent flickering
			camera.resetZoomLevel();//reset zoom back to default
			p_GUI->toggle_pause();//set pause to true thus pausing the game
		}
		if (p_Input->KeyReleased(GLFW_KEY_ESCAPE))
		{
			p_GUI->pause_switch = false;//set pause to false, exit pause menu
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
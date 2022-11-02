/*!*************************************************************************
****
\file LevelEditor.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 2
\date 28-9-2022
\brief  Header file for LevelEditor.cpp
****************************************************************************
***/
#pragma once
#include "Platform/Window/Window.h"

#define p_Editor EM::LevelEditor::GetInstance()

namespace EM {
	class LevelEditor
	{
	public:
		//ctor and dtor
		LevelEditor() = default;
		~LevelEditor() = default;

		//main function for running
		void Init(Window* window);
		void Update();	//update loop
		void Draw();
		void End();

		void ContentBrowser();
		void Logger();
		void Profiler();
		void Hierarchy();
		void Inspector();
		void Audio();

		static std::unique_ptr<LevelEditor>& GetInstance();
		//for inspector and Hierarchy
		bool mDebugDraw{ false };
	
	private:
		void MainMenuBar();
		void Docking();
		bool FullScreenMode{};
		bool Pad{};

	private:
		ImGuiDockNodeFlags dock_space_flags{};
		Window* m_window{nullptr};
		static std::unique_ptr<LevelEditor> m_instance;
		//profiler
		bool b_profile = false;
		float m_SceneRuntime = 0.0f;
		float m_UpdateTimer = 0.0f;
		std::array<float, 5> mSystemRunTime = { 0.0f,0.0f,0.0f,0.0f };
		//for inspector and Hierarchy
		Entity selectedEntity{};
	};
}
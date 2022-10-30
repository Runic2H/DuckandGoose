/*!*************************************************************************
****
\file LevelEditor.h
\author Cheung Jun Yin Matthew
\par DP email: j.cheung@digipen.edu
\par Course: csd2400
\par Section: a
\par Milestone 1
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

		void DropDownMenu(); //Menu widget
		void ColorPickerTab(); //color picker widget
		void EditorTabs();
		void TransformTab();
		void SpriteRenderer();
		void SceneHierarchyWindow();

		static std::unique_ptr<LevelEditor>& GetInstance();
	private:
		void docking();
		bool dockspaceOpen{};
		bool fullscreenMode{};
		bool pad{};
		void Profiler();

	private:
		std::set<Entity> mEntities;
		ImGuiDockNodeFlags dock_space_flags{};
		Window* m_window{nullptr};
		static std::unique_ptr<LevelEditor> m_instance;
		
	};
}
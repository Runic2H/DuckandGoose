#include "../ECS/SceneManager.h"
#include "MenuScript.h"


namespace EM {

	MenuScript::MenuScript() :SelectedScene{""} {}

		void MenuScript::Start(){}

		void MenuScript::Update(float Frametime)
		{
			/*if (SelectedScene != "")
			{
				p_Scene->DeserializeFromFile(SelectedScene);
				SelectedScene = "";
			}*/
			auto& transform = p_ecs.GetComponent<Transform>(GetScriptEntityID());
			//auto& rigidbody = p_ecs.GetComponent<RigidBody>(GetScriptEntityID());
			auto& tag = p_ecs.GetComponent<NameTag>(GetScriptEntityID());
			auto& logic = p_ecs.GetComponent<Logic>(GetScriptEntityID());
			auto& col = p_ecs.GetComponent<Collider>(GetScriptEntityID());
			auto& btn = p_ecs.GetComponent<Button>(GetScriptEntityID());

			

			//std::cout << btn.CheckIfclicked();
			if (btn.CheckIfclicked())
			{
				std::cout << "clicked";
				p_Scene->setSceneToLoad("Assets/Scene/Level.json");
				btn.Toggleclicked();
			}
			
			

			/*if (GLFW_KEY_2)
			{
				SelectedScene = "Assets/Scene/HowToPlay.json";
			}
			*/
		}

		void MenuScript::End()
		{
			delete this;
		}


		IScript* MenuScript::Clone() const
		{
			return new MenuScript(*this);
		}
		std::string MenuScript::GetScriptName()
		{
			return "MenuScript";
		}


}
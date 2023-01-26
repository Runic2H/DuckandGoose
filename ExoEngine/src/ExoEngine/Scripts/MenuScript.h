#pragma once

#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/ECS/Types.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/ECS/ECS.h"
#include "ExoEngine/Input/Input.h"
//#include "ExoEngine/GUI/GUI.h"


namespace EM
{
	class MenuScript : public IScript
	{
	public:
		MenuScript();
		~MenuScript() = default;

		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;

		virtual IScript* Clone() const override;
		virtual std::string GetScriptName() override;
	private:
		std::string SelectedScene;
	};
}
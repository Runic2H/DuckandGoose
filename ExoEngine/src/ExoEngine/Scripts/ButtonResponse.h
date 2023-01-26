#pragma once
#include "empch.h"
#include "ExoEngine/Scripts/IScript.h"
#include"ExoEngine/Input/Input.h"
#include"ExoEngine/Math/Math.h"
#include"Platform/Window/Window.h"
#include "ExoEngine/ECS/Types.h"
#include "ExoEngine/ECS/ECS.h"
#include <vector>
namespace EM {
	class ButtonResponse : public IScript
	{
	public:
		ButtonResponse() = default;
		~ButtonResponse() = default;
		/*!*************************************************************************
		This function initialises the script. As there are no data members that require
		initialization, this function is empty
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		This function runs the logic of the script to check for collision and apply
		a counter-force to the entity's current velocity which is calculated based on
		the current velocity and the collision normal
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		This function ends the script by deleting the pointer to this script
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		This function clones the script by allocating and constructing a copy of this
		script and returning it
		****************************************************************************/
		virtual ButtonResponse* Clone() const override;
		/*!*************************************************************************
		This function returns the purpose of the script as a flag for when it is called
		****************************************************************************/
		virtual std::string GetScriptName() override;

		bool is_within_box(glm::vec2 cur, Collider box);
		
		bool clicked;
		bool selected;

	private:
		struct button_bb
		{
			vec2D min;
			vec2D max;
		};
		button_bb Button_BoundingBox{};

		
	
	};
}


		

		
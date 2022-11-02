/*!*************************************************************************
****
\file PlayerMovement.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for basic movement for player

****************************************************************************
***/

#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"


namespace EM
{
	class PlayerMovement : public IScript
	{
	public:
		PlayerMovement() = default;
		~PlayerMovement() = default;
		virtual PlayerMovement* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual std::string GetScriptName() override;
	private:
		entityPhysics phys;
	};
}
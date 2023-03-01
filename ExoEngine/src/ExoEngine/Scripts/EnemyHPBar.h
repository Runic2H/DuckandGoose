/*!*************************************************************************
****
\file EnemyHPBar.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief	Script for Enemy HP Bar

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "ExoEngine/Math/physics.h"
#include "Platform/Graphics/Camera2D.h"
#include "Platform/Graphics/Graphics.h"
#include "GLFW/glfw3.h"

namespace EM
{
	/*!*************************************************************************
	Class for Enemy HP Bar Script
	****************************************************************************/
	class EnemyHPBar : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Enemy HP Bar
		****************************************************************************/
		EnemyHPBar();
		/*!*************************************************************************
		Default destructor for Enemy HP Bar
		****************************************************************************/
		~EnemyHPBar() = default;
		/*!*************************************************************************
		Returns a new copy of EnemyHPBar Script
		****************************************************************************/
		virtual EnemyHPBar* Clone() const override;
		/*!*************************************************************************
		Start State of EnemyHPBar Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update Loop of Enemy HP Bar Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for Enemy HP Bar
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override;
		
		//inline static Camera2D camera { -1.0f, 1.0f, -1.0f , 1.0f };
	private:
		float mCurrCooldown = 0; //for shield or dash
	};
}
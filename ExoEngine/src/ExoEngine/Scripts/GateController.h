/*!*************************************************************************
****
\file GateController.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Gate Controller

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once
#include "IScript.h"
#include "ExoEngine/Input/Input.h"
#include "GLFW/glfw3.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	/*!*************************************************************************
	Class for Gate Controller Script
	****************************************************************************/
	class GateController : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Gate Controller
		****************************************************************************/
		GateController();
		/*!*************************************************************************
		Default destructor for Gate Controller
		****************************************************************************/
		~GateController() = default;
		/*!*************************************************************************
		Returns a new copy of GateController Script
		****************************************************************************/
		virtual GateController* Clone() const override;
		/*!*************************************************************************
		Start State of GateController Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update Loop of GateController Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for GateController
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override;

		int enemies;

	private:
		
	};
}
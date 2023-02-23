/*!*************************************************************************
****
\file LaserTurret.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Laser Turret

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
	Class for Laser Turret Script
	****************************************************************************/
	class LaserTurret : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Laser Turret
		****************************************************************************/
		LaserTurret();
		/*!*************************************************************************
		Default destructor for Player Controller
		****************************************************************************/
		~LaserTurret() = default;
		/*!*************************************************************************
		Returns a new copy of LaserTurret Script
		****************************************************************************/
		virtual LaserTurret* Clone() const override;
		/*!*************************************************************************
		Start State of LaserTurret Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update Loop of LaserTurret Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for LaserTurret
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override;


	private:
		float timeTilSpawn;
		float startTimeTilSpawn;
		float firingDuration;
		float startFiringDuration;
		int damage;
		bool playerDetected;
		bool firing;
	};
}
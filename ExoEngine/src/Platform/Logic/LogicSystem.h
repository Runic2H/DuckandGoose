/*!*************************************************************************
****
\file LogicSystem.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Logic System used for iterating through each entity with a logic
component, grabbing the vector of scripts from the logic components and
iterating through each script to call its update functions

****************************************************************************
***/

#pragma once
#include "Platform/System/System.h"
#include "ExoEngine/ECS/Components/Components.h"
#include "ExoEngine/ECS/ECS.h"

namespace EM
{
	class LogicSystem : public System
	{
	public:
		virtual std::string GetName() { return "LogicSystem"; }
		virtual void Init() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
	};
}
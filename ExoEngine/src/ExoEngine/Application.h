/*!*************************************************************************
****
\file			Application.h
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			28-9-2022
\brief			This file contain the neccesary declaration functions for class Application.

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#pragma once

#include "Core.h"
#include "Log.h"
#include "Platform/System/SystemManager.h"
#include "ECS/ECS.h"

namespace EM {
	class EM_API Application
	{

	public:
		enum class state
		{
			pause,
			play,
			quit
		};
		
		Application();
		virtual ~Application(); // will be override
		void SystemInput(System* system);
		void Run();				//run the application 
		void End();

	private:
	};
	 
	//To be defined in CLIENT
	Application* CreateApplication();
}


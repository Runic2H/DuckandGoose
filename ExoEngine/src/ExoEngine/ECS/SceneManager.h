/*!*************************************************************************
****
\file SceneManager.h
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief  This file contains all the functions for loading and unloading the
level data into a JSON file. Currently on application end the ecs will be
saved into a json file for future loading

****************************************************************************
***/

#pragma once
#include "ECS.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "Platform/System/SystemManager.h"
#include "Types.h"
#include "empch.h"
#include "Serialization/JSONserialization.h"
#include "Serialization/JSONincludes.h"

#define p_Scene EM::SceneManager::GetInstance()

namespace EM
{

	class SceneManager : public JSONSerializer
	{
	public:

		static std::unique_ptr<SceneManager>& GetInstance();

		void Init();

		virtual bool Deserialize(const rapidjson::Value& obj);

		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;
		
	private:
		static std::unique_ptr<SceneManager> m_instance;
	};
}
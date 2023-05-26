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

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
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
		/*!*************************************************************************
		Returns an instance of the SceneManager
		****************************************************************************/
		static std::unique_ptr<SceneManager>& GetInstance();

		/*!*************************************************************************
		Initialize all registered components
		****************************************************************************/
		void Init();
		/*!*************************************************************************
		Deserializes ECS entities and data from JSON file to build ECS (File loading)
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes ECS entities and data to JSON file to save ECS (File saving)
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		// temp: scene to load code
		void setSceneToLoad(std::string s);
		void checkForSceneToLoad();
		void changeScene(std::string s);
		
		bool isGameplay;
	private:
		// Unique pointer to SceneManager
		static std::unique_ptr<SceneManager> m_instance;

		std::string sceneToLoad;
	};
}
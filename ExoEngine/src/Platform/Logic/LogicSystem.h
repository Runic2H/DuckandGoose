#pragma once
#include "Platform/System/System.h"
#include "ExoEngine/ECS/Components/Components.h"

namespace EM
{
	class EM_API LogicSystem : public System
	{
		std::set<Entity> mEntities;
		virtual std::string GetName() = 0;
		virtual ~LogicSystem() {};
		virtual void Init() = 0 {};
		virtual void Update(float Frametime) { float frametime };
		virtual void End() = 0 {};
	};
}
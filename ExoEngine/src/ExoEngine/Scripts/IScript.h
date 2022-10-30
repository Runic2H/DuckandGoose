#pragma once
#include "ExoEngine/ECS/Types.h"
#include "empch.h"
#include "ExoEngine/ECS/Components/NameTag.h"

namespace EM
{
	class IScript
	{
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void End() = 0;
	private:
		Entity entityID;
		NameTag nametag;
	};
}
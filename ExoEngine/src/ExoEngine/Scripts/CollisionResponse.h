#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/ECS/Types.h"
#include "ExoEngine/ECS/ECS.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class CollisionResponse : public IScript
	{
	public:
		CollisionResponse() = default;
		~CollisionResponse() = default;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual CollisionResponse* Clone() const override;
		virtual std::string GetScriptName() override;
	private:
		entityPhysics mPhys;
	};
}
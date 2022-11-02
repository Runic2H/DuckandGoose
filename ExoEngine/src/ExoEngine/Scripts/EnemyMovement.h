#pragma once
#include "ExoEngine/Scripts/IScript.h"
#include "ExoEngine/Math/Vmath.h"
#include "ExoEngine/Math/physics.h"

namespace EM
{
	class EnemyMovement : public IScript
	{
	public:
		EnemyMovement() = default;
		~EnemyMovement() = default;
		virtual EnemyMovement* Clone() const override;
		virtual void Start() override;
		virtual void Update(float Frametime) override;
		virtual void End() override;
		virtual std::string GetScriptName() override;
	private:
		entityPhysics mPhys;
	};
}
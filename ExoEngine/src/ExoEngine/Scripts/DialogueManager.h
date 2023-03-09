/*!*************************************************************************
****
\file DialogueManager.h
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 2/11/2022
\brief	Script for Dialogue Manager

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
	Class for Dialogue Manager Script
	****************************************************************************/
	class DialogueManager : public IScript
	{
	public:
		/*!*************************************************************************
		Default constructor for Dialogue Manager
		****************************************************************************/
		DialogueManager();
		/*!*************************************************************************
		Default destructor for Dialogue Manager
		****************************************************************************/
		~DialogueManager() = default;
		/*!*************************************************************************
		Returns a new copy of Dialogue Manager Script
		****************************************************************************/
		virtual DialogueManager* Clone() const override;
		/*!*************************************************************************
		Start State of DialogueManager Script
		****************************************************************************/
		virtual void Start() override;
		/*!*************************************************************************
		Update Loop of DialogueManager Script
		****************************************************************************/
		virtual void Update(float Frametime) override;
		/*!*************************************************************************
		End State for DialogueManager
		****************************************************************************/
		virtual void End() override;
		/*!*************************************************************************
		Returns the name of Script
		****************************************************************************/
		virtual std::string GetScriptName() override;

		virtual void SetScriptEntityID(Entity& entity) override { entityID = entity; }

		virtual Entity& GetScriptEntityID() override { return entityID; }

	private:
		std::ostream mTextStream;
		const char mTextBuffer[300];
		float mPrintSpeed;
	};
}
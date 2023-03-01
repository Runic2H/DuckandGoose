/*!*************************************************************************
****
\file EnemyHPBar.cpp
\author Tan Ek Hern
\par DP email: t.ekhern@digipen.edu
\par Course: CSD2400
\par Section: a
\par Assignment GAM200
\date 28/01/2023
\brief	Script for Enemy HP Bar

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "EnemyHPBar.h"

namespace EM
{
    /*!*************************************************************************
    Default constructor for Enemy HP Bar
    ****************************************************************************/
    EnemyHPBar::EnemyHPBar() {}
    /*!*************************************************************************
    Returns a new copy of EnemyHPBar Script
    ****************************************************************************/
    EnemyHPBar* EnemyHPBar::Clone() const
	{
		return new EnemyHPBar(*this);
	}
    /*!*************************************************************************
    Start State of EnemyHPBar Script
    ****************************************************************************/
	void EnemyHPBar::Start()
	{

	}
    /*!*************************************************************************
    Update Loop of EnemyHPBar Script
    ****************************************************************************/
	void EnemyHPBar::Update(float Frametime)
	{
        
	}
    /*!*************************************************************************
    End State for EnemyHPBar
    ****************************************************************************/
    void EnemyHPBar::End()
    {
        delete this;
    }
    /*!*************************************************************************
    Returns the name of Script
    ****************************************************************************/
    std::string EnemyHPBar::GetScriptName()
    {
        return "EnemyHPBar";
    }
}
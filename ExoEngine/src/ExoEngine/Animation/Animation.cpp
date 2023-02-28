/*!*************************************************************************
****
\file			ResourceManager.cpp
\author			Huang Xin Xiang
\par DP email:	h.xinxiang@digipen.edu
\par Course:	Gam200
\section		A
\date			11-11-2022
\brief			This file sets frame data for animations

Copyright (C) 20xx DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of Technology is prohibited.
****************************************************************************
***/
#include "empch.h"
#include "Animation.h"


namespace EM {
	
	/*!*************************************************************************
	Constructor for animation
	****************************************************************************/
	Animation::Animation()
	{

	}

	/*!*************************************************************************
	Add frame information
	****************************************************************************/
	void Animation::AddFrameInfo(Sprite& sprite)
	{
		sprite.GetDisplayTime().resize(sprite.GetMaxIndex());//resize the number of frames in a sprite
	}


	/*!*************************************************************************
	Update animations based on delta time
	****************************************************************************/
	void Animation::UpdateAnimation(float deltatime, Sprite& sprite)
	{

		sprite.internaltimer += deltatime;
		
		if (sprite.internaltimer >= sprite.GetDisplayTime()[sprite.GetIndex().x].second)
		{
			sprite.GetIndex().x++;
			sprite.internaltimer = 0.0f;
			if (sprite.GetIndex().x >= sprite.GetMaxIndex())
			{
				sprite.GetIndex().x = 0;
			}
			
		}

	}

}
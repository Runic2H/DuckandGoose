#include "empch.h"
#include "Animation.h"


namespace EM {
	

	Animation::Animation()
		:frames(0), CurrentFrameIndex(0), currentFrameTime(0)
	{

	}
	void Animation::AddFrameInfo(Sprite& sprite)
	{
		FrameData data;
		data.TextureId = GETTEXTURE(sprite.GetTexture())->GetRendererID();
		data.DisplayTime = sprite.GetDisplayTime();
		data.FrameIndex = sprite.GetIndex();
		sprite.GetIndex().x = CurrentFrameIndex;
		data.MaxFrame = 8.0f;
		frames.push_back(data);
	}
	void Animation::FrameIncrement()
	{
		CurrentFrameIndex++;
	}
	const Animation::FrameData* Animation::GetCurrentFrame() const
	{
		if (frames.size() > 0)
			return &frames[(int)CurrentFrameIndex];

		return nullptr;
	}
	bool Animation::UpdateAnimation(float deltatime)
	{
		if (frames.size() > 0)
		{
			currentFrameTime += deltatime;
			if (currentFrameTime >= frames[(int)CurrentFrameIndex].DisplayTime )
			{
				currentFrameTime = 0.0f;
				FrameIncrement();
				if (CurrentFrameIndex >= 8.0f)
					ResetFrame();
				return true;
			}
		}
		return false;
	}
	void Animation::ResetFrame()
	{
		CurrentFrameIndex = 0;
		currentFrameTime = 0;
	}
}
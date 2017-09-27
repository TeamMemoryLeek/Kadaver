#pragma once
#include "Kadaver/Core/Core.h"
#include "Kadaver/Core/Math/Vector3.h"
#include "SoundBuffer.h"

KD_NAMESPACE_BEGIN

// TODO: Dynamic positioning
class KD_CORE_DLL AudioListener
{
public:
	AudioListener(const Vector3& position = Vector3::zero, 
		const float& rotation = 0.f);
	void playFromSource(SoundBuffer* buffer, Vector3 source);

	Vector3 position_;
	float rotation_;

	void setActiveListener(AudioListener* listener)
	{
		activeListener_ = listener;
	}

private:
	static AudioListener* activeListener_;
};

KD_NAMESPACE_END
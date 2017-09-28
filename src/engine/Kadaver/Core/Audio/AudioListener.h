#pragma once
#include "Kadaver/Core/Core.h"
#include "Kadaver/Core/Math/Vector3.h"
#include "AudioBuffer.h"

KD_NAMESPACE_BEGIN

// TODO: Dynamic positioning
class KD_CORE_DLL AudioListener
{
public:
	AudioListener(const Vector3& position = Vector3::zero, 
		const float& rotation = 0.f);
	void apply(AudioBuffer* buffer, Vector3 source);

	Vector3 position_;
	float rotation_;

	static AudioListener* activeListener_;
};

KD_NAMESPACE_END
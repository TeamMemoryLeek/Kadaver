#pragma once
#include "Kadaver/Core/Core.h"
#include "Kadaver/Core/Math/Vector3.h"
#include "AudioBuffer.h"

KD_NAMESPACE_BEGIN

class KD_CORE_DLL AudioSource
{
public:
	AudioSource(const Vector3& position = Vector3::zero);

	Vector3 position_;
	
	void addBuffer(AudioBuffer* buffer);
	void removeBuffer(AudioBuffer* buffer);
	void playBuffer(AudioBuffer* buffer);

	void update();
private:
	static const uint MAX_NUM_BUFFERS = 16;
	AudioBuffer* buffers_[MAX_NUM_BUFFERS];
	uint numBuffers_;
};

KD_NAMESPACE_END
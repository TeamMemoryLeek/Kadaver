#pragma once
#include "Kadaver/Core/Core.h"
#include "Kadaver/Core/Math/Vector3.h"
#include "SoundBuffer.h"

KD_NAMESPACE_BEGIN

class KD_CORE_DLL AudioSource
{
public:
	AudioSource(const Vector3& position = Vector3::zero);

	Vector3 position_;
	
	void addBuffer(SoundBuffer* buffer);
	void removeBuffer(SoundBuffer* buffer);
	void playBuffer(SoundBuffer* buffer);

	void update();
private:
	static const uint MAX_NUM_BUFFERS = 16;
	SoundBuffer* buffers_[MAX_NUM_BUFFERS];
	uint numBuffers_;
};

KD_NAMESPACE_END
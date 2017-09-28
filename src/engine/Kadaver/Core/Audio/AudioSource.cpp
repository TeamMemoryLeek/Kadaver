#include "AudioSource.h"
#include "AudioListener.h"
#include <assert.h>

KD_NAMESPACE_BEGIN

AudioSource::AudioSource(const Vector3& position /*= Vector3::zero*/)
	: position_(position)
{
	memset(buffers_, 0, sizeof(buffers_));
}

void kd::AudioSource::addBuffer(AudioBuffer* buffer)
{
	assert(numBuffers_ < MAX_NUM_BUFFERS);
	buffers_[numBuffers_++] = buffer;;
}

void kd::AudioSource::removeBuffer(AudioBuffer* buffer)
{
	for (uint i = 0; i < numBuffers_; i++)
	{
		if (buffers_[i] == buffer)
		{
			buffers_[i] = nullptr;

			if (i < numBuffers_ - 1)
			{
				buffers_[i] = buffers_[numBuffers_ - 1];
				buffers_[numBuffers_ - 1] = nullptr;
			}

			numBuffers_--;
		}
	}
}

void kd::AudioSource::playBuffer(AudioBuffer* buffer)
{
	bool inArray = false;
	for (AudioBuffer* b : buffers_)
	{
		if (b && b == buffer)
			inArray = true;
	}
	if (!inArray)
		addBuffer(buffer);

	update();
	buffer->play();
}

void kd::AudioSource::update()
{
	// Tweak buffer settings from active listener
	AudioListener* listener = AudioListener::activeListener_;
	if (!listener)
		return;

	for (AudioBuffer* buffer : buffers_)
	{
		if(!buffer)
			continue;
		listener->apply(buffer, position_);
	}
}

KD_NAMESPACE_END


#include "AudioListener.h"

KD_NAMESPACE_BEGIN

AudioListener* AudioListener::activeListener_ = nullptr;

AudioListener::AudioListener(const Vector3& position /*= Vector3::zero*/, 
	const float& rotation /*= 0.f*/)
	: position_(position)
	, rotation_(rotation)
{
	if (!activeListener_)
		activeListener_ = this;
}

void kd::AudioListener::apply(AudioBuffer* buffer, Vector3 source)
{
	// Calculate distance
	float distance = (source - position_).lengthSquared();
	float volume = 1 / (distance * 0.003f + 1.f);

	// Calculate panning
	Vector3 listenerToSource = (source - position_).normalized();
	Vector3 direction = Vector3(sin(rotation_), 0.f, cos(rotation_));
	direction.normalize();
	source.y = 0.f;

	Vector3 cross = direction.cross(listenerToSource);
	float pan = cross.y;

	// Audio behind listener should have less volume
	float dot = direction.dot(listenerToSource);
	if (dot < 0.f)
	{
		dot = 1.0f + (dot * 0.05f);
		volume *= dot;
	}

	buffer->setVolume(volume);
	buffer->setPan(pan * 0.4f);
}

KD_NAMESPACE_END


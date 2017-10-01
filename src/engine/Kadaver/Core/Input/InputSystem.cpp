#include "InputSystem.h"
#include "../Window.h"

KD_NAMESPACE_BEGIN

bool InputSystem::keys_[NUM_KEYS];
bool InputSystem::keysPrev_[NUM_KEYS];

InputSystem::InputSystem()
{
	memset(&keys_[0], 0, sizeof(keys_));
	memset(&keysPrev_[0], 0, sizeof(keysPrev_));

	kd::Window::setKeyCallback(keyCallback);
}

void kd::InputSystem::update()
{
	memcpy(&keysPrev_, &keys_, sizeof(keys_));
}

void InputSystem::keyCallback(int action, int key)
{
	if (action == KD_ACTION_DOWN)
	{
		keys_[key] = true;
	}
	else if (action == KD_ACTION_UP)
	{
		keys_[key] = false;
	}
}

bool InputSystem::getKeyPressed(uint key) const
{
	return keys_[key] && !keysPrev_[key];
}

bool InputSystem::getKeyReleased(uint key) const
{
	return !keys_[key] && keysPrev_[key];
}

bool InputSystem::getKeyHeld(uint key) const
{
	return keys_[key];
}

KD_NAMESPACE_END

#pragma once

#include "Kadaver/Core/Core.h"

KD_NAMESPACE_BEGIN

class KD_CORE_DLL InputSystem
{
public:
	InputSystem();

	void update();

	bool getKeyPressed(uint key) const;
	bool getKeyReleased(uint key) const;
	bool getKeyHeld(uint key) const;

private:
	static const uint NUM_KEYS = 256;
	static bool keys_[NUM_KEYS];
	static bool keysPrev_[NUM_KEYS];

	static void keyCallback(int action, int key);
};

KD_NAMESPACE_END


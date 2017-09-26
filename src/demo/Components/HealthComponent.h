#pragma once

#include <Kadaver/Core/GameObject/Component.h>

class HealthComponent : public kd::Component
{
public:
	static kd::Component* deserialize(kd::GameObject* go);

	HealthComponent(kd::GameObject* go);

	void init() override;
	void update() override;

};
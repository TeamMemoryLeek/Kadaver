#pragma once

#include <Kadaver/Core/GameObject/Component.h>

COMPONENT_CLASS(TransformComponent)
{
public:
	TransformComponent(kd::GameObject* go);
	
	void init() override;
	void update() override;
};
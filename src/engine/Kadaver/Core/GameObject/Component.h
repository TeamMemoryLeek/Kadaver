#pragma once

#include "Kadaver/Core/Core.h"
#include "GameObject.h"

#define COMPONENT_CLASS(NAME) \
class NAME : public kd::Component

// TODO: Take json data as parameter
#define COMPONENT_DESERIALIZE(NAME) \
static kd::Component* _kd_component_deserialize(kd::GameObject* go); \
static bool _kd_component_reg = kd::GameObject::regComponent( \
#NAME, _kd_component_deserialize); \
static kd::Component* _kd_component_deserialize(kd::GameObject* go)

KD_NAMESPACE_BEGIN

class KD_CORE_DLL Component
{
public:
	Component(GameObject* go)
		: gameObject_(go)
	{
	}
	virtual void init() = 0;
	virtual void update() = 0;
protected:
	GameObject* gameObject_;
};

KD_NAMESPACE_END
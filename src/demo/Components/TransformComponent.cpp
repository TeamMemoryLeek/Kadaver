#include "TransformComponent.h"

COMPONENT_DESERIALIZE(TransformComponent)
{
	TransformComponent* c = new TransformComponent(go);
	return c;
}

TransformComponent::TransformComponent(kd::GameObject* go)
	: Component(go)
{
}

void TransformComponent::init()
{

}

void TransformComponent::update()
{

}
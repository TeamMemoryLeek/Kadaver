#include "HealthComponent.h"

bool reg = kd::GameObject::regComponent("HealthComponent", HealthComponent::deserialize);

kd::Component* HealthComponent::deserialize(kd::GameObject* go)
{
	HealthComponent* c = knew HealthComponent(go);
	return c;
}

HealthComponent::HealthComponent(kd::GameObject* go)
	: kd::Component(go)
{

}

void HealthComponent::init()
{
}

void HealthComponent::update()
{
}


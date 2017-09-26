#include "GameObject.h"
#include "Component.h"

KD_NAMESPACE_BEGIN

GameObject::ComponentRegistry* 
GameObject::componentRegistry_ = knew GameObject::ComponentRegistry;

bool kd::GameObject::regComponent(std::string name, deserializeFunc func)
{
	(*componentRegistry_)[name] = func;
	return true;
}

GameObject::GameObject()
{
	create();
}

GameObject::GameObject(const char* path)
{
	create();
	createFromFile(path);
}

void GameObject::create()
{
	components_.reserve(4);
}

void GameObject::createFromFile(const char* path)
{
	KD_UNUSED(path);

	for (auto it : *componentRegistry_)
	{
		// TODO: Check if json key matches registry key
		deserializeFunc func = it.second;
		Component* c = func(this);
		components_.push_back(c);
	}
}

void GameObject::init()
{
	for (auto c : components_)
	{
		c->init();
	}
}

void GameObject::update(float deltaTime)
{
	KD_UNUSED(deltaTime);
	for (auto c : components_)
	{
		c->update();
	}
}

KD_NAMESPACE_END
#pragma once

#include "Kadaver/Core/Core.h"
#include <vector>
#include <map>
#include <string>

KD_NAMESPACE_BEGIN

class Component;

class KD_CORE_DLL GameObject
{
public:
	typedef Component*(*deserializeFunc)(GameObject*);
	typedef std::map<std::string, deserializeFunc> ComponentRegistry;
	static ComponentRegistry* componentRegistry_;

	static bool regComponent(std::string name, deserializeFunc func);

	GameObject();
	GameObject(const char* path);
private:
	void create();
	void createFromFile(const char* path);
public:
	void init();
	void update(float deltaTime);
private:
	std::vector<Component*> components_;
};

KD_NAMESPACE_END
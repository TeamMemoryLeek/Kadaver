#pragma once
#ifdef LIB_CORE
#define CORE_DLL __declspec(dllexport)
#else
#define CORE_DLL __declspec(dllimport)
#endif


class CORE_DLL Object
{
public:
	Object();
	Object(int i);

	int fooBar() const;

private:
	int i_;
};

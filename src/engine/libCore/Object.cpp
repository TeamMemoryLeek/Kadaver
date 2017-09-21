#include "Object.h"

#include <stdio.h>


Object::Object()
	: i_(0)
{
}

Object::Object(int i)
	: i_(i)
{
}

int Object::fooBar() const
{
	return printf("%d\n", i_);
}

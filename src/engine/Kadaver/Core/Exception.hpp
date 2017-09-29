#pragma once

#include <exception>
#include <string>

namespace kd
{

class Exception : public std::exception
{
public:
	Exception(const std::string& message = "")
		: message_(message)
	{
	}

	virtual const char* what() const noexcept 
	{ 
		return message_.c_str(); 
	}
private:
	std::string message_;
};

}
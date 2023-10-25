#pragma once
#include <exception>
#include <string>
#include <winerror.h>
#include <stdio.h>

// COM Exception
class com_exception : public std::exception
{
private:
	HRESULT result;
	std::string description;

public:
	com_exception(HRESULT hr) : com_exception(hr, "") {}
	com_exception(HRESULT hr, std::string msg) : result(hr), description(msg) {}
	virtual const char* what() const override
	{
		static char str[512]{};
		sprintf_s(str, "Failed with HRESULT : %08X\n%s\n", result, description.c_str());
		return str;
	}
};

inline void ThrowIfFailed(HRESULT hr, std::string msg = "")  //inline ram이 아닌 cpu의 레지스터에 잠깐저장, 매개변수가 작아야지만 가능
{
	if (FAILED(hr))
	{
		throw com_exception(hr, msg);
	}
}
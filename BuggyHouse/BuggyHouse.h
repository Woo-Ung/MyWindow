#pragma once

#include <list>
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"

class BuggyHouse : public D2DFramework
{
private:
	std::list<std::shared_ptr<Actor>> mBugList;
	std::shared_ptr<Actor> mspBackground;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR titile = L"BuggyHouse",
		UINT width = 1024, UINT height = 768) override;
	virtual void Render() override;
	virtual void Release() override;
};


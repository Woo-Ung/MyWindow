#include "Bug.h"

Bug::Bug(D2DFramework* pFramework) : 
	Actor(pFramework, L"Images/bug.png")
{
	RECT rct{};
	GetClientRect(pFramework->GetHWND(), &rct);

	mX = static_cast<float>(rand() % (rct.right - rct.left));
	mY = static_cast<float>(rand() % (rct.bottom - rct.top));

	mDirection = Direction::UP;
	mSteps = 0.0f;
}

void Bug::Draw()
{
	if (mSteps++ > 30)
	{
		mSteps = 0;
		int dir = static_cast<int>(mDirection);
		int count = static_cast<int>(Direction::COUNT);

		dir += (rand() % 3 - 1);
		dir = (dir + count) % count;

		mDirection = static_cast<Direction>(dir);
	}
	switch (mDirection)
	{
	case Direction::UP:
		mY--;
		break;
	case Direction::UP_RIGHT:
		mY--;
		mX++;
		break;
	case Direction::RIGHT:		
		mX++;
		break;
	case Direction::DOWN_RIGHT:
		mY++;
		mX++;
		break;
	case Direction::DOWN:
		mY++;
		break;
	case Direction::DOWN_LEFT:
		mY++;
		mX--;
		break;
	case Direction::LEFT:
		mX--;
		break;
	case Direction::UP_LEFT:
		mY--;
		mX--;
		break;
	}

	Actor::Draw();
}

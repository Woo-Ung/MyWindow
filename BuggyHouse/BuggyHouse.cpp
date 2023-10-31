#include "BuggyHouse.h"
#include "Bug.h"

HRESULT BuggyHouse::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;
    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr, "Failed in D2DFramework::Initialize()");

    mspBackground = std::make_shared<Actor>(this, L"Images/back.png", 0.0f, 0.0f, 1.0f);
     
    for (int i = 0; i < 40;i++)
    {       
        mBugList.push_back(std::make_shared<Bug>(this));
    }

    return S_OK;
}

void BuggyHouse::Render()
{  
    mspRenderTarget->BeginDraw();
    mspRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    CheckBugs();

    mspBackground->Draw();
    for (auto& bug : mBugList)
    {
        bug->Draw();
    }

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BuggyHouse::Release()
{
    for (auto& bug : mBugList)
    {
        bug.reset();
    }
    mBugList.clear();
    mspBackground.reset();

    D2DFramework::Release();
}

void BuggyHouse::CheckBugs()
{
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 )
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(mHwnd, &pt);
        
        auto itr = std::remove_if(mBugList.begin(), mBugList.end(),
            [&] (auto& actor) {
                Bug* p = static_cast<Bug*>(actor.get());
                p->IsClicked(pt);
                if (p->mIsDead)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        );

        mBugList.erase(itr, mBugList.end());
    }
}

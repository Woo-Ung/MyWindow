//Library
//	선언(.h)과 정의(.cpp - .lib)
//	zip Libaray
//
//API // Library 모음
//	Application Programming Interface
//	앱을 만들 때 사용하는 모든 기능
//	앱 <=> 운영체제
//
//SDK // Library + API
//	Software Development kit
//	API를 포함한 기타 여러 유틸리티의 묶음
//
//Framework // SDK+규칙
//	위에서 설명한 모든 도구들의 모음이면서 규칙

#include <windows.h>
#include "ImageExample.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    try
    {
        ImageExample myFramework;

        myFramework.Initialize(hInstance, L"Framework",1024,768);

        int ret = myFramework.GameLoop();
        
        myFramework.Release();

        return ret;
    }
    catch (const com_exception& e)
    {
        OutputDebugStringA(e.what());
        MessageBoxA(nullptr, e.what(), "Error", MB_OK);
    }

    return 0;
}

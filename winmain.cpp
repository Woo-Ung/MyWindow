#include <Windows.h>

//API : Application Programming Interface
// Windows API
//	Win16 - 80186, 80286
//	Win32 - 80386  486 586 (pentium)
//		win32s
//	Win32	Win64
//
//	C언어
//
//MFC : Microsoft Foundation Class library
//	C++ 언어
//	비주얼편집기, 나름 스마트포인터
//	어럽다. 마이크로소프트도 포기함
//	(2014년 중단, 차라리 visual basic사용)
//
//	>WTL : Windows Template Library
//		MFC가 너무 어려움 -> 사내에서 별도의 라이브러리를 만들어서 사용
//		오픈소스 -> 여전히 업데이트
//
//Windows Form
//	.NET 환경
//	MFC 대체자 (2014 중단)
//
//WPF : Windows Presentation Platform
//	최초의 하드웨어 가속
//	게임 개발자 흥미 X
//
//Windows RT (Runtime)
//	윈도우 8, 윈도우폰
//
//UWP : Universal Windows Platfrom
//	윈도우 10
//	윈도우 스토어에 등록할 앱은 반드시 UWP로 만드세요

//수업 Win 32 API
//SAl : sourcecod Annotation Langugae
//
//HINSTANCE
//	Handle of Instance
//	Pointer to Instance
//
//	Instance

//LPSTR
//	Long Pointer(to null-terminatied) STRing
//	char*
//
//HWND
//	Handle of Window
//
//LPCTSTR
//	Long Pointer Constant TChar String
//
//UINT
//	Unsigned Integer
// DWORD
//	Double Word - 4byte(32bit) == int
// Word
//	16bit == short
// LPVOID
//	Long Pointer Void
//


//헝가리언 표기법
	// 타입의 약자를 접두어로 표기

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//entrt point
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,
					_In_ int nShowCmd)
{
	/*MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONEXCLAMATION | MB_OKCANCEL);*/


	// 1. '윈도우클래스' 등록
	WNDCLASSEX wc{};
	//***important***
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // 초기화. 구조체를 만들면 반드시 해야함
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
		return 0;
	}

	// 2. '윈도우'를 생성
	HWND hwnd;
	hwnd = CreateWindowEx(
		0,
		gClassName,
		L"Hello Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		MessageBox(nullptr, L"Failed to create", L"Error", MB_OK);
		return 0;
	}
	
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	
	// 3. '윈도우메시지'를 처리
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// 4. '윈도우프로시저' 작성
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
			break;
	}
}
#include <Windows.h>

//API : Application Programming Interface
// Windows API
//	Win16 - 80186, 80286
//	Win32 - 80386  486 586 (pentium)
//		win32s
//	Win32	Win64
//
//	C���
//
//MFC : Microsoft Foundation Class library
//	C++ ���
//	���־�������, ���� ����Ʈ������
//	���. ����ũ�μ���Ʈ�� ������
//	(2014�� �ߴ�, ���� visual basic���)
//
//	>WTL : Windows Template Library
//		MFC�� �ʹ� ����� -> �系���� ������ ���̺귯���� ���� ���
//		���¼ҽ� -> ������ ������Ʈ
//
//Windows Form
//	.NET ȯ��
//	MFC ��ü�� (2014 �ߴ�)
//
//WPF : Windows Presentation Platform
//	������ �ϵ���� ����
//	���� ������ ��� X
//
//Windows RT (Runtime)
//	������ 8, ��������
//
//UWP : Universal Windows Platfrom
//	������ 10
//	������ ���� ����� ���� �ݵ�� UWP�� ���弼��

//���� Win 32 API
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


//�밡���� ǥ���
	// Ÿ���� ���ڸ� ���ξ�� ǥ��

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//entrt point
int WINAPI WinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,
					_In_ int nShowCmd)
{
	/*MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONEXCLAMATION | MB_OKCANCEL);*/


	// 1. '������Ŭ����' ���
	WNDCLASSEX wc{};
	//***important***
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // �ʱ�ȭ. ����ü�� ����� �ݵ�� �ؾ���
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

	// 2. '������'�� ����
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
	
	// 3. '������޽���'�� ó��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// 4. '���������ν���' �ۼ�
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
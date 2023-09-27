#include <Windows.h>
#include <sstream>
#include <gdiplus.h>

#pragma comment (lib,"Gdiplus.lib")

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
	Gdiplus::GdiplusStartupInput gpsi;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gpsi, nullptr);

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
	RECT wr = { 0,0,640,480 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd;
	hwnd = CreateWindowEx(
		0,
		gClassName,
		L"Hello Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right-wr.left,
		wr.bottom-wr.top,
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

	Gdiplus::GdiplusShutdown(gdiToken);
	return msg.wParam;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	//HPEN redPen = CreatePen(PS_SOLID, 1,RGB(255,0,0));
	//HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255,0,0));

	//SelectObject(hdc, redPen);
	//SelectObject(hdc, hatchBrush);
	//Rectangle(hdc, 0, 0, 100, 100);

	//DeleteObject(hatchBrush);
	//DeleteObject(redPen);

	Gdiplus::Pen redPen(Gdiplus::Color(255,255,0,0));
	Gdiplus::HatchBrush hatchBrush(Gdiplus::HatchStyle::HatchStyleCross, Gdiplus::Color(255, 255, 0, 0));
	Gdiplus::Image image(L"image.png");

	Gdiplus::Graphics graphics(hdc);
	/*graphics.DrawRectangle(&redPen, 0, 0, 100, 100);*/
	graphics.DrawImage(&image, 0, 0,600,600);

	EndPaint(hwnd, &ps);	
}

// 4. '���������ν���' �ۼ�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)	//LRESULT : Long Result
{																					//			pointer
	switch (message)																// 
	{																				// CALLBACK : �ݹ��Լ�
	case WM_PAINT:																	//		(����� ������ �ü���� �˾Ƽ� �ҷ���)
	{																				// 
		OnPaint(hwnd);																// WPARAM : WORD Parameter
																					// LPARAM : Long ptr Parameter
		break;
	}
	
	case WM_KEYDOWN:																
	{																				
		std::ostringstream oss;														
		oss << "virtual keycod = " << wParam << std::endl;							
		OutputDebugStringA(oss.str().c_str());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		std::ostringstream oss;		
		oss << "x : " << LOWORD(lParam) << ", y : " << HIWORD(lParam) << std::endl;
		
		OutputDebugStringA(oss.str().c_str());
		break;
	}
	case WM_CLOSE:	//WM : Window Message
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

// Graphics
//
// GDI : Graphics Device Interface
// 
// WinG : Windows for Gaming	(������)
// 
// DirectDraw	(������)
//	�ϵ���� ����(Hardware Accelerate)
// 
// GDI+	(������)
// 
// Direct2D
// 
// DirectX
//	Direct2d
//	Direct3d
//	..
// 
// GDI : Graphics Device Interface
//	
//	BRUSH
//	PEN
//	����
//	
//	Event Driven System
//		Callback Function
// 
//
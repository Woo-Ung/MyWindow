








int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	

	InitD3D();

	MSG msg{};
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			//GAME
			RenderFrame();
		}

	}

	DestroyD3D();

	return static_cast<int>(msg.wParam);
}

void InitD3D()
{
	
}

void OnResize() //창 전체화면 전환시
{
	
}

void RenderFrame()
{
	
}

void DestroyD3D()
{
	
}


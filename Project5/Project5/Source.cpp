#include <Windows.h>

// Global function declaration 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszcmdline, int icmdshow)
{
	//Local Var
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	char AppName[] = "Windows";

	//Code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//registration
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,
		"Window Paint On Keydown",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, icmdshow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	static COLORREF colourB = RGB(0,0,0);
	static HBRUSH hMyBrush;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		   case 'R':
			   colourB = RGB(255, 0, 0);
		   break;

		   case 'B':
			   colourB = RGB(0, 0, 255);
		   break;

		   case 'K':
			   colourB = RGB(0, 0, 0);
			   break;

		   case 'G':
			   colourB = RGB(0, 255, 0);
			   break;

		   case 'Y':
			   colourB = RGB(255, 255, 0);
			   break;

		   case 'W':
			   colourB = RGB(255, 255, 255);
			   break;

		   case 'C':
			   colourB = RGB(0, 255, 255);
			   break;

		   case 'M':
			   colourB = RGB(255, 0, 255);
			   break;

		   default:
			   colourB = RGB(125, 125, 125);
			   break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hMyBrush = CreateSolidBrush(colourB);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hMyBrush);
		int a = FillRect(hdc,&rc,hMyBrush);
		DeleteObject(hMyBrush);
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
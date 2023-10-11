#include <Windows.h>

// Global function declaration 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global Var
static char LButtonDown = 'A';

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
		"Text On Keydown",
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
	COLORREF colourT = RGB(0, 255, 0);
	COLORREF colourB = RGB(0, 0, 0);

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		LButtonDown = 'k';
		InvalidateRect(hwnd, NULL, FALSE);
	break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, colourT);
		SetBkColor(hdc, colourB);
		if (LButtonDown == 'k')
		{
			DrawText(hdc,
				"Shubhangi",
				-1,
				&rc,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
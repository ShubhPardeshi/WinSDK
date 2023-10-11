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
		"Multiple Message Window",
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

	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, "WM_CREATE Message is sent", "Shubhangi", MB_OK | MB_ICONEXCLAMATION);
		break;

	case WM_MOVE:
		MessageBox(hwnd,"WM_MOVE Message is sent","Shubhangi", MB_OKCANCEL | MB_ICONINFORMATION);
		break;

	case WM_SIZE:
		MessageBox(hwnd, "WM_SIZE Message is sent", "Shubhangi", MB_OKCANCEL);
		break;

	case WM_KEYDOWN:
		MessageBox(hwnd, "WM_KEYDOWN Message is sent", "Shubhangi", MB_OK | MB_ICONERROR);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "WM_LBUTTONDOWN Message is sent", "Shubhangi", MB_OK | MB_ICONSTOP);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
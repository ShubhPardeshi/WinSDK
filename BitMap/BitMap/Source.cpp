#include <Windows.h>
#include "Resource.h"

// Global function declaration 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);

struct In
{
	char name[50];
	char address[50];
};

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//registration
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,
		"BitMap",
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
	HDC hdc,hdc2;
	HGDIOBJ hGDIObj;
	PAINTSTRUCT ps;
	BITMAP bmp;
	RECT rc;
	static HBITMAP hBitmap1 ;
	HWND hwndGoto = NULL;
	HINSTANCE  hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWL_HINSTANCE);

	switch (iMsg)
	{
	case WM_CREATE:
		hBitmap1 = LoadBitmap(hInst, MAKEINTRESOURCE(MY_BITMAP));
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);

		hdc = BeginPaint(hwnd,&ps);
		hdc2 = CreateCompatibleDC(hdc);

		hGDIObj = SelectObject(hdc2, hBitmap1);
		GetObject(hBitmap1, sizeof(BITMAP), (LPSTR)&bmp);
		StretchBlt(hdc, 0,0, rc.right, rc.bottom, hdc2,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);

		SelectObject(hdc2, hBitmap1);
		DeleteDC(hdc2);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN: 
		DialogBox(hInst,"DATAENTRY",hwnd,DlgProc);	
		break;
		
	case WM_DESTROY:
		DeleteObject(hBitmap1);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	In in;
	switch (iMsg)
	{
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, ID_EDITNAME));
			SendDlgItemMessage(hDlg,ID_RBMARRIED,BM_SETCHECK,1,0);
			return(TRUE);
			break;

		case WM_COMMAND:
			switch (wParam)
			{
			case ID_OK:
				GetDlgItemText(hDlg,ID_EDITNAME,in.name,50);
				GetDlgItemText(hDlg,ID_EDITADDRESS,in.address,50);
				EndDialog(hDlg,0);
				break;

			case ID_CANCEL:
				EndDialog(hDlg, 0);
				break;
			}
			return(TRUE);
	}
	return (FALSE);

}



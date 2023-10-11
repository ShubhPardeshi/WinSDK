#define UNICODE
#include<Windows.h>
#include"Header.h"

//Global Function Declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//Global Variable Declaration 
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   //variable Declaration 
	WNDCLASSEX WndClass;
	HWND hWnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COMClient");
	HRESULT hr;

	//COM Initialization 
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COMliberary cannot be initiallized.\n Program will now exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//WndClassEx Initialization
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.lpfnWndProc = WndProc;
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_APPSTARTING);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = AppName;
	WndClass.lpszMenuName = NULL;
	WndClass.hIconSm = LoadIcon(NULL, IDI_HAND);

    //Register class
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(AppName,TEXT("Client Of COM Dll Server"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	CoUninitialize();
	return(int)msg.wParam;
}


//Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Function Declaration
	void SafeInterfaceRelease(void);

	HRESULT hr;
	int iNum1, iNum2, iSum, iSub;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);

		if (FAILED(hr))
		{
			MessageBox(hWnd,TEXT("Interface cannot be obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hWnd);
		}
        iNum1 = 555;
		iNum2 = 45;
		
		pISum->SumOfTwoInt(iNum1,iNum2,&iSum);
		wsprintf(str,TEXT("sum of %d and %d =%d"),iNum1,iNum2,iSum);
		MessageBox(hWnd,str,TEXT("Result"),MB_OK);

		hr = pISum->QueryInterface(IID_ISubtract,(void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hWnd,TEXT("Interface cannot be obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hWnd);
		}
		pISum->Release();
		pISum = NULL;

		pISubtract->SubtractionOfTwoInt(iNum1,iNum2,&iSub);
		wsprintf(str, TEXT("Subraction of %d and %d = %d"), iNum1, iNum2, iSub);
		MessageBox(hWnd, str, TEXT("Result"), MB_OK);
		pISubtract->Release();
		pISubtract = NULL;
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd,iMsg,wParam,lParam));
}

















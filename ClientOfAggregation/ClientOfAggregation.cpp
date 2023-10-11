#define UNICODE
#include<Windows.h>
#include "ClientOfAggregatio.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ISum *pISum = NULL;
ISubstraction *pISubstract = NULL;
IMultiplication*pIMultiplication = NULL;
IDivision *pIDivision = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Variable declaration
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("COMClient");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("COM Library Can Not br Initialized.\nProgram will ow exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	//code
	//Initialization ofWNDCLASSEX
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = szAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Register above class
	RegisterClassEx(&wndClass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("Client of Containment Component."),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	void SafeInterfaceRelease(void);
	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_CSumCubstraction, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("ISum interface cannot be obtained."), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 100;
		iNum2 = 45;
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result of SUM"), MB_OK);
		hr = pISum->QueryInterface(IID_ISubstraction, (void**)&pISubstract);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("ISubstract interface cannot be obtained."), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 45;
		pISubstract->SubstractionOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Substraction of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result of SUBSTRACTION"), MB_OK);
		hr = pISubstract->QueryInterface(IID_Multiplication, (void**)&pIMultiplication);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("IMultiplication interface cannot be obtained."), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISubstract->Release();
		pISubstract = NULL;

		iNum1 = 12;
		iNum2 = 30;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Multiplication of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result of MULTIPLICAION"), MB_OK);
		hr = pIMultiplication->QueryInterface(IID_Division, (void**)&pIDivision);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("IDivision interface cannot be obtained."), TEXT("Program Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 99;
		iNum2 = 9;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Division of %d and %d = %d"), iNum1, iNum2, iSum);
		MessageBox(NULL, str, TEXT("Result of DIVISION"), MB_OK);
		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubstract)
	{
		pISubstract->Release();
		pISubstract = NULL;
	}
	if (pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}
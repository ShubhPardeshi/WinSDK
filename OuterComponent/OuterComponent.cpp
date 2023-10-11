#define UNICODE
#include<Windows.h>
#include "OuterComponent.h"
#include "InnerComponent.h"

class CSumSubstration : public ISum, ISubstraction, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	CSumSubstration();
	~CSumSubstration();

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

	HRESULT __stdcall InitializeInnerComponent();
};

class CSumSubstractionClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSubstractionClassFactory();
	~CSumSubstractionClassFactory();

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

CSumSubstration::CSumSubstration()
{
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubstration::~CSumSubstration()
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}

	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}

HRESULT CSumSubstration::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubstraction)
		*ppv = static_cast<ISubstraction *>(this);
	else if (riid == IID_Multiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_Division)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubstration::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubstration::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return(m_cRef);
}

HRESULT CSumSubstration::SubstractionOfTwoIntegers(int num1, int num2, int *pSub)
{
	*pSub = num1 - num2;
	return(S_OK);
}

HRESULT CSumSubstration::DivisionOfTwoIntegers(int num1, int num2, int *pDiv)
{
	*pDiv = num1 / num2;
	return(S_OK);
}

HRESULT CSumSubstration::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubstration::MultiplicationOfTwoIntegers(int num1, int num2, int *pMul)
{
	*pMul = num1 * num2;
	return(S_OK);
}

HRESULT CSumSubstration::InitializeInnerComponent()
{
	HRESULT hr;

	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_Multiplication, (void **)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Multiplication Interface cannot be obtained from Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	hr = m_pIMultiplication->QueryInterface(IID_Division, (void **)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Division Interface cannot be obtained from Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}

CSumSubstractionClassFactory::CSumSubstractionClassFactory()
{
	m_cRef = 1;
}
CSumSubstractionClassFactory::~CSumSubstractionClassFactory()
{

}

HRESULT CSumSubstractionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubstractionClassFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubstractionClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return(m_cRef);
}

HRESULT CSumSubstractionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubstration *pCSumSubstract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubstract = new CSumSubstration;
	if (pCSumSubstract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubstract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT(" Failed to initialized Inner Component."), TEXT("ERROR"), MB_OK);
		pCSumSubstract->Release();
		return(E_FAIL);
	}
	hr = pCSumSubstract->QueryInterface(riid, ppv);
	pCSumSubstract->Release();
	return(hr);
}

HRESULT CSumSubstractionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubstractionClassFactory *pCSumSubstractionClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_CSumCubstraction)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCSumSubstractionClassFactory = new CSumSubstractionClassFactory;
	if (pCSumSubstractionClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubstractionClassFactory->QueryInterface(riid, ppv);
	pCSumSubstractionClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}


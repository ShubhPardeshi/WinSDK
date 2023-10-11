class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubstraction : public IUnknown
{
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*) = 0;
};

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision :public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// {55A89FD1-F15C-4158-A04A-9395744B43F0}
const CLSID CLSID_CSumCubstraction = { 0x55a89fd1, 0xf15c, 0x4158, 0xa0, 0x4a, 0x93, 0x95, 0x74, 0x4b, 0x43, 0xf0 };

// {B4F45CEC-47EF-4317-91DC-77B0EA85B123}
const IID IID_ISum = { 0xb4f45cec, 0x47ef, 0x4317, 0x91, 0xdc, 0x77, 0xb0, 0xea, 0x85, 0xb1, 0x23 };

// {D6096A8C-0BDC-4C3F-BB15-CA5D265D4873}
const IID IID_ISubstraction = { 0xd6096a8c, 0xbdc, 0x4c3f, 0xbb, 0x15, 0xca, 0x5d, 0x26, 0x5d, 0x48, 0x73 };

// {CA03FB64-1816-40F2-AF3A-71203C8388BB}
const IID IID_Multiplication = { 0xca03fb64, 0x1816, 0x40f2, 0xaf, 0x3a, 0x71, 0x20, 0x3c, 0x83, 0x88, 0xbb };

// {4A5A41DA-804E-4E6E-A831-81890C690798}
const IID IID_Division = { 0x4a5a41da, 0x804e, 0x4e6e, 0xa8, 0x31, 0x81, 0x89, 0xc, 0x69, 0x7, 0x98 };

#pragma once

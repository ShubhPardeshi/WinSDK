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

// {F24A8A38-0A6F-40A4-87EC-3271450332DB}
const CLSID CLSID_MultiplicationDivision = { 0xf24a8a38, 0xa6f, 0x40a4, 0x87, 0xec, 0x32, 0x71, 0x45, 0x3, 0x32, 0xdb };

// {CA03FB64-1816-40F2-AF3A-71203C8388BB}
const IID IID_Multiplication = { 0xca03fb64, 0x1816, 0x40f2, 0xaf, 0x3a, 0x71, 0x20, 0x3c, 0x83, 0x88, 0xbb };

// {4A5A41DA-804E-4E6E-A831-81890C690798}
const IID IID_Division = { 0x4a5a41da, 0x804e, 0x4e6e, 0xa8, 0x31, 0x81, 0x89, 0xc, 0x69, 0x7, 0x98 };


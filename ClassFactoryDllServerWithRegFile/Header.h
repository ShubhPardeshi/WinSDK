#pragma once
class ISum : public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoInt(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoInt(int,int,int*) = 0;
};

//Clsid
// {8A9E1ACC-3A0F-4446-BE3C-C81630FA23D7}
const CLSID CLSID_SumSubtract =
{ 0x8a9e1acc, 0x3a0f, 0x4446, 0xbe, 0x3c, 0xc8, 0x16, 0x30, 0xfa, 0x23, 0xd7 };

// {8C6FBA2E-0336-46A1-B05C-BFD5A5ED8707}
const IID IID_ISum = 
{0x8c6fba2e, 0x336, 0x46a1, 0xb0, 0x5c, 0xbf, 0xd5, 0xa5, 0xed, 0x87, 0x7};

// {7F6C0476-6AC6-4D9E-9BA6-A74D22B035A2}
const IID IID_ISubtract = 
{0x7f6c0476, 0x6ac6, 0x4d9e, 0x9b, 0xa6, 0xa7, 0x4d, 0x22, 0xb0, 0x35, 0xa2};

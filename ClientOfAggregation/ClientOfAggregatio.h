#pragma once
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

// {61906C63-75D2-4BDF-BE28-93926DC33C09}
const CLSID CLSID_CSumCubstraction = { 0x61906c63, 0x75d2, 0x4bdf, 0xbe, 0x28, 0x93, 0x92, 0x6d, 0xc3, 0x3c, 0x9 };

// {12A89471-6CAB-4286-809F-5BBE914C01D4}
const IID IID_ISum = { 0x12a89471, 0x6cab, 0x4286, 0x80, 0x9f, 0x5b, 0xbe, 0x91, 0x4c, 0x1, 0xd4 };

// {E926F7A3-9F98-4B97-BE65-AA89C4F81202}
const IID IID_ISubstraction = { 0xe926f7a3, 0x9f98, 0x4b97, 0xbe, 0x65, 0xaa, 0x89, 0xc4, 0xf8, 0x12, 0x2 };

// {9EADA16E-148B-4266-9750-42C08515219B}
const CLSID CLSID_MultiplicationDivision = { 0x9eada16e, 0x148b, 0x4266, 0x97, 0x50, 0x42, 0xc0, 0x85, 0x15, 0x21, 0x9b };

// {6FC3454B-ED40-4647-977F-BB703EE1E441}
const IID IID_Multiplication = { 0x6fc3454b, 0xed40, 0x4647, 0x97, 0x7f, 0xbb, 0x70, 0x3e, 0xe1, 0xe4, 0x41 };

// {879D22E4-4065-4716-84D1-A0E28923B43D}
const IID IID_Division = { 0x879d22e4, 0x4065, 0x4716, 0x84, 0xd1, 0xa0, 0xe2, 0x89, 0x23, 0xb4, 0x3d };


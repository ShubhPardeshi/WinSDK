#pragma once
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

// {9EADA16E-148B-4266-9750-42C08515219B}
const CLSID CLSID_MultiplicationDivision = { 0x9eada16e, 0x148b, 0x4266, 0x97, 0x50, 0x42, 0xc0, 0x85, 0x15, 0x21, 0x9b };

// {6FC3454B-ED40-4647-977F-BB703EE1E441}
const IID IID_Multiplication = { 0x6fc3454b, 0xed40, 0x4647, 0x97, 0x7f, 0xbb, 0x70, 0x3e, 0xe1, 0xe4, 0x41 };

// {879D22E4-4065-4716-84D1-A0E28923B43D}
const IID IID_Division = { 0x879d22e4, 0x4065, 0x4716, 0x84, 0xd1, 0xa0, 0xe2, 0x89, 0x23, 0xb4, 0x3d };


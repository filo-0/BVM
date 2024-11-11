#include <cstring>

#include "bvm.hpp"

namespace BVM
{
    void PopByte0()
	{
		FunctionStack::LocalB(GetNextByte().UValue, 0).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte1()
	{
		FunctionStack::LocalB(GetNextByte().UValue, 1).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte2()
	{
		FunctionStack::LocalB(GetNextByte().UValue, 2).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte3()
	{
		FunctionStack::LocalB(GetNextByte().UValue, 3).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord0()
	{
		FunctionStack::LocalH(GetNextByte().UValue, 0).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord2()
	{
		FunctionStack::LocalH(GetNextByte().UValue, 1).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopWord()
	{
		FunctionStack::LocalW(GetNextByte().UValue) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord0()
	{
		FunctionStack::LocalW(0) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord1()
	{
		FunctionStack::LocalW(1) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord2()
	{
		FunctionStack::LocalW(2) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord3()
	{
		FunctionStack::LocalW(3) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopDWord()
	{
		FunctionStack::LocalD(GetNextByte().UValue) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord0()
	{
		FunctionStack::LocalD(0) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord1()
	{
		FunctionStack::LocalD(1) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord2()
	{
		FunctionStack::LocalD(2) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord3()
	{
		FunctionStack::LocalD(3) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopWords()
	{
		HWord params = GetNextHWord();
		u32 count = params.BValue[1].UValue;
		std::memcpy(&FunctionStack::LocalW(params.BValue[0].UValue), OperationStack::TopWs(count), count * sizeof(Word));
		OperationStack::PopWs(count);
	}
} // namespace BVM

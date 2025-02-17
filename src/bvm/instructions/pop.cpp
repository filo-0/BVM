#include <cstring>

#include "bvm.hpp"

namespace BVM
{
	void PopWord()
	{
		FunctionStack::SetLocalW(GetNextByte().UValue, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord0()
	{
		FunctionStack::SetLocalW(0 ,OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord1()
	{
		FunctionStack::SetLocalW(1, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord2()
	{
		FunctionStack::SetLocalW(2, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord3()
	{
		FunctionStack::SetLocalW(3, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopDWord()
	{
		FunctionStack::SetLocalD(GetNextByte().UValue, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord0()
	{
		FunctionStack::SetLocalD(0, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord1()
	{
		FunctionStack::SetLocalD(1, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord2()
	{
		FunctionStack::SetLocalD(2, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord3()
	{
		FunctionStack::SetLocalD(3, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopWords()
	{
		u8 loc =   GetNextByte().UValue;
		u8 count = GetNextByte().UValue;
		
		for (u8 i = 0; i < count; i++)
			FunctionStack::SetLocalW(loc + i, OperationStack::TopW(count - i - 1));
		OperationStack::PopWs(count);
	}
} // namespace BVM

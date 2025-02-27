#include <cstring>

#include "bvm.hpp"

namespace BVM
{
	void PopWord()
	{
		FunctionScope::SetLocalW(GetNextByte().UValue, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord0()
	{
		FunctionScope::SetLocalW(0 ,OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord1()
	{
		FunctionScope::SetLocalW(1, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord2()
	{
		FunctionScope::SetLocalW(2, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopWord3()
	{
		FunctionScope::SetLocalW(3, OperationStack::TopW());
		OperationStack::PopW();
	}
	void PopDWord()
	{
		FunctionScope::SetLocalD(GetNextByte().UValue, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord0()
	{
		FunctionScope::SetLocalD(0, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord1()
	{
		FunctionScope::SetLocalD(1, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord2()
	{
		FunctionScope::SetLocalD(2, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopDWord3()
	{
		FunctionScope::SetLocalD(3, OperationStack::TopD());
		OperationStack::PopD();
	}
	void PopWords()
	{
		u8 loc =   GetNextByte().UValue;
		u8 count = GetNextByte().UValue;
		
		for (u8 i = 0; i < count; i++)
			FunctionScope::SetLocalW(loc + i, OperationStack::TopW(count - i - 1));
		OperationStack::PopWs(count);
	}
} // namespace BVM

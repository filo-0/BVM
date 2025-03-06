#include <cstring>

#include "bvm.hpp"

namespace BVM
{
	void PopByte0()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalB(loc, 0, OperationStack::TopW().BValue[0]);
		OperationStack::PopW();
	}
	void PopByte1()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalB(loc, 1, OperationStack::TopW().BValue[0]);
		OperationStack::PopW();
	}
	void PopByte2()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalB(loc, 2, OperationStack::TopW().BValue[0]);
		OperationStack::PopW();
	}
	void PopByte3()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalB(loc, 3, OperationStack::TopW().BValue[0]);
		OperationStack::PopW();
	}
	void PopHWord0()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalH(loc, 0, OperationStack::TopW().HValue[0]);
		OperationStack::PopW();
	}
	void PopHWord2()
	{
		u8 loc = GetNextByte().UValue;
		FunctionScope::SetLocalH(loc, 1, OperationStack::TopW().HValue[0]);
		OperationStack::PopW();
	}
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

#include "bvm.hpp"
#include "assertion.hpp"

namespace BVM
{
    void Call()
	{
		u16 funcID = GetNextHWord().UValue;
		u32 funcPointer = FunctionPointerPool[funcID];
		u32 prevProgramCounter = ProgramCounter;

		ProgramCounter = funcPointer;
		u8 argSize = GetNextByte().UValue;
		u8 localSize = GetNextByte().UValue;

		Word* data = OperationStack::TopWs(argSize);
		FunctionStack::OnCall(prevProgramCounter, localSize);
		FunctionStack::PushData(data, argSize);
		OperationStack::PopWs(argSize);
		OperationStack::OnCall();
	}
	void SysCall()
	{
		switch (GetNextByte().UValue)
		{
		case OpCodes::Syscall::Print: PrintString(); break;
		case OpCodes::Syscall::PrintI64: PrintI64(); break;
		case OpCodes::Syscall::PrintF64: PrintF64(); break;
		case OpCodes::Syscall::SqrtF32: CallSqrtF32(); break;
		case OpCodes::Syscall::SqrtF64: CallSqrtF64(); break;
		default: ASSERT(false, "System call function not implemented!"); break;
		}
	}
	void ReturnVoid()
	{
		u32 prevProgramCounter = FunctionStack::OnReturn();
		OperationStack::OnReturn();

		ProgramCounter = prevProgramCounter;	
	}
	void ReturnByte()
	{
		u8 ret = (u8)OperationStack::TopW().UValue; OperationStack::PopW();

		u32 prevProgramCounter = FunctionStack::OnReturn();
		OperationStack::OnReturn();
		OperationStack::PushW(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnHWord()
	{
		u16 ret = (u16)OperationStack::TopW().UValue; OperationStack::PopW();

		u32 prevProgramCounter = FunctionStack::OnReturn();
		OperationStack::OnReturn();
		OperationStack::PushW(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnWord()
	{
		Word ret = OperationStack::TopW(); OperationStack::PopW();

		u32 prevProgramCounter = FunctionStack::OnReturn();
		OperationStack::OnReturn();
		OperationStack::PushW(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnDWord()
	{
		DWord ret = OperationStack::TopD(); OperationStack::PopD();

		u32 prevProgramCounter = FunctionStack::OnReturn();
		OperationStack::OnReturn();
		OperationStack::PushD(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnWords()
	{
		u8 count = Bytecode[ProgramCounter++];
		Word* ret = OperationStack::TopWs(count); OperationStack::PopWs(count);

		u32 prevProgramPointer = FunctionStack::OnReturn();
		OperationStack::OnReturn();
		OperationStack::PushWs(ret, count);

		ProgramCounter = prevProgramPointer;
	}

	void PrintString()
	{
		std::cout << (const char*)OperationStack::TopD().Pointer;
		OperationStack::PopD();
	}
	void PrintI64()
	{
		std::cout << OperationStack::TopD().IValue;
		OperationStack::PopD();
	}
	void PrintF64()
	{
		std::cout << OperationStack::TopD().FValue;
		OperationStack::PopD();
	}
	void CallSqrtF32()
	{
		OperationStack::TopW().FValue = std::sqrt(OperationStack::TopW().FValue);
	}
	void CallSqrtF64()
	{
		OperationStack::TopD().FValue = std::sqrt(OperationStack::TopD().FValue);
	}
} // namespace BVM

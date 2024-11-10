#include <iostream>
#include <cmath>

#include "bvm.hpp"
#include "assertion.hpp"

namespace BVM
{
    void Call()
	{
		u16 funcID = GetNextHWord().UValue;
		u32 funcPointer = FunctionPointerPool[funcID];

		PrevStackStates.emplace_back(
				ProgramCounter,
				FunctionStack::GetBasePointer(),
				OperationStack::GetBasePointer()
			);

		ProgramCounter = funcPointer;
		u8 argSize = GetNextByte().UValue;
		u8 localSize = GetNextByte().UValue;

		Word* data = OperationStack::TopWs(argSize);
		FunctionStack::PushData(data, argSize);
		FunctionStack::OnCall(localSize);
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
		StackState& prevState = PrevStackStates.back();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
	
	}
	void ReturnByte()
	{
		StackState& prevState = PrevStackStates.back();
		u8 ret = OperationStack::TopW().UValue; OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
	}
	void ReturnHWord()
	{
		StackState& prevState = PrevStackStates.back();
		u16 ret = OperationStack::TopW().UValue; OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
	}
	void ReturnWord()
	{
		StackState& prevState = PrevStackStates.back();
		Word ret = OperationStack::TopW(); OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
	}
	void ReturnDWord()
	{
		StackState& prevState = PrevStackStates.back();
		DWord ret = OperationStack::TopD(); OperationStack::PopD();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushD(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
	}
	void ReturnWords()
	{
		StackState& prevState = PrevStackStates.back();
		u8 count = Bytecode[ProgramCounter++];
		Word* ret = OperationStack::TopWs(count); OperationStack::PopWs(count);

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushWs(ret, count);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop_back();
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

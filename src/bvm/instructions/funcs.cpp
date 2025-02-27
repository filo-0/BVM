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
		u16 stackSize = GetNextHWord().UValue;

		Word* data = OperationStack::TopWs(argSize);
		Stack::PushScope(data, argSize, localSize, stackSize, prevProgramCounter);
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
		case OpCodes::Syscall::Scan: Scan(); break;
		case OpCodes::Syscall::ScanI64: ScanI64(); break;
		case OpCodes::Syscall::ScanF64: ScanF64(); break;
		case OpCodes::Syscall::MemCopy: MemCopy(); break;
		case OpCodes::Syscall::NanoTime   : NanoTime();    break;
		default: ASSERT(false, "System call function not implemented!"); break;
		}
	}
	void ReturnVoid()
	{
		u32 prevProgramCounter = Stack::PopScope();

		ProgramCounter = prevProgramCounter;	
	}
	void ReturnWord()
	{
		Word ret = OperationStack::TopW();

		u32 prevProgramCounter = Stack::PopScope();
		OperationStack::PushW(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnDWord()
	{
		DWord ret = OperationStack::TopD();

		u32 prevProgramCounter = Stack::PopScope();
		OperationStack::PushD(ret);

		ProgramCounter = prevProgramCounter;
	}
	void ReturnWords()
	{
		u8 count = Bytecode[ProgramCounter++];
		Word* ret = OperationStack::TopWs(count);

		u32 prevProgramCounter = Stack::PopScope();
		OperationStack::PushWs(ret, count);

		ProgramCounter = prevProgramCounter;
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
		f32 x = OperationStack::TopW().FValue;
		OperationStack::PopW();
		OperationStack::PushW(std::sqrt(x));
	}
	void CallSqrtF64()
	{
		f64 x = OperationStack::TopD().FValue;
		OperationStack::PopD();
		OperationStack::PushD(std::sqrt(x));
	}
	void Scan()
	{
		u32 max = OperationStack::TopW().UValue;
		char *buffer = (char*)OperationStack::TopD(1).Pointer;
		std::cin.getline(buffer, max);
	}
	void ScanI64()
	{
		i64 val;
		std::cin >> val;
		OperationStack::PushD(val);
	}
	void ScanF64()
	{
		f64 val;
		std::cin >> val;
		OperationStack::PushD(val);
	}
	void MemCopy()
	{
		u32 n = OperationStack::TopW().UValue;
		void* dest = OperationStack::TopD(1).Pointer;
		void* src = OperationStack::TopD(3).Pointer;
		memcpy(src, dest, n);
	}
	void NanoTime()
	{
		i64 nanoTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		OperationStack::PushD(nanoTime);
	}
} // namespace BVM

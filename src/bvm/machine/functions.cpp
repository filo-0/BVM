#include <cstring>
#include <iostream>
#include <cmath>

#include "bvm.hpp"
#include "assertion.hpp"

namespace BVM::Machine
{
    inline static Byte GetNextByte() { return Bytecode[ProgramCounter++]; }
	inline static HWord GetNextHWord()
	{
		u16 v = *reinterpret_cast<u16*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u16);
		return v;
	}
	inline static Word GetNextWord()
	{
		u32 v = *reinterpret_cast<u32*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u32);
		return v;
	}
	inline static DWord GetNextDWord()
	{
		u64 v = *reinterpret_cast<u64*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u64);
		return v;
	}

    void Exit() { Running = false; }
	#pragma region Push&Pop
	void PushByte0()  { OperationStack::PushW(FunctionStack::LocalB0(GetNextByte().UValue)); }
	void PushByte1()  { OperationStack::PushW(FunctionStack::LocalB1(GetNextByte().UValue)); }
	void PushByte2()  { OperationStack::PushW(FunctionStack::LocalB2(GetNextByte().UValue)); }
	void PushByte3()  { OperationStack::PushW(FunctionStack::LocalB3(GetNextByte().UValue)); }
	void PushHWord0() { OperationStack::PushW(FunctionStack::LocalH0(GetNextByte().UValue)); }
	void PushHWord2() { OperationStack::PushW(FunctionStack::LocalH2(GetNextByte().UValue)); }
	void PushWord()   { OperationStack::PushW(FunctionStack::LocalW(GetNextByte().UValue));  }
	void PushWord0()  { OperationStack::PushW(FunctionStack::LocalW(0));                     }
	void PushWord1()  { OperationStack::PushW(FunctionStack::LocalW(1));                     }
	void PushWord2()  { OperationStack::PushW(FunctionStack::LocalW(2));                     }
	void PushWord3()  { OperationStack::PushW(FunctionStack::LocalW(3));                     }
	void PushDWord()  { OperationStack::PushD(FunctionStack::LocalD(GetNextByte().UValue));  }
	void PushDWord0() { OperationStack::PushD(FunctionStack::LocalD(0));                     }
	void PushDWord1() { OperationStack::PushD(FunctionStack::LocalD(1));                     }
	void PushDWord2() { OperationStack::PushD(FunctionStack::LocalD(2));                     }
	void PushDWord3() { OperationStack::PushD(FunctionStack::LocalD(3));                     }
	void PushWords()
	{
		HWord params = GetNextHWord();
		OperationStack::PushWs(&FunctionStack::LocalW(params.B.Value0.UValue), params.B.Value1.UValue);
	}
	void PushWordValue0()  { OperationStack::PushW(0); }
	void PushDWordValue0() { OperationStack::PushD(0); }
	void PushI32_1() { OperationStack::PushW(1);    }
	void PushI32_2() { OperationStack::PushW(2);    }
	void PushI64_1() { OperationStack::PushD(1);    }
	void PushI64_2() { OperationStack::PushD(2);    }
	void PushF32_1() { OperationStack::PushW(1.0f); }
	void PushF32_2() { OperationStack::PushW(2.0f); }
	void PushF64_1() { OperationStack::PushD(1.0);  }
	void PushF64_2() { OperationStack::PushD(2.0);  }
	void PushI8AsI32() { OperationStack::PushW(GetNextByte().IValue); }
	void PushI8AsI64() { OperationStack::PushD(GetNextByte().IValue); }
	void PushWordFromPool()      { OperationStack::PushW(WordConstantPool[GetNextByte().UValue]);   }
	void PushWordFromPoolWide()  { OperationStack::PushW(WordConstantPool[GetNextHWord().UValue]);  }
	void PushDWordFromPool()     { OperationStack::PushD(DWordConstantPool[GetNextByte().UValue]);  }
	void PushDWordFromPoolWide() { OperationStack::PushD(DWordConstantPool[GetNextHWord().UValue]); }

	void PopByte0()
	{
		FunctionStack::LocalB0(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte1()
	{
		FunctionStack::LocalB1(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte2()
	{
		FunctionStack::LocalB2(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte3()
	{
		FunctionStack::LocalB3(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord0()
	{
		FunctionStack::LocalH0(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord2()
	{
		FunctionStack::LocalH2(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
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
		u32 count = params.B.Value1.UValue;
		std::memcpy(&FunctionStack::LocalW(params.B.Value0.UValue), OperationStack::TopWs(count), count * sizeof(Word));
		OperationStack::PopWs(count);
	}
#pragma endregion
	#pragma region Dup&Swap
	void DupWord() { OperationStack::DupW(); }
	void DupWordX1() { OperationStack::DupWX1(); }
	void DupWordX2() { OperationStack::DupWX2(); }
	void DupDWord() { OperationStack::DupD(); }
	void DupDWordX1() { OperationStack::DupDX1(); }
	void DupDWordX2() { OperationStack::DupDX2(); }
	void SwapWord() { OperationStack::SwapW(); }
	void SwapDWord() { OperationStack::SwapD(); }
#pragma endregion
	#pragma region Load&Store
	void GetAddress()  { OperationStack::PushD(reinterpret_cast<u64>(&FunctionStack::LocalW(Bytecode[ProgramCounter++]))); }
	void LoadByte0()   { OperationStack::LoadB0();  }
	void LoadByte1()   { OperationStack::LoadB1();  }
	void LoadByte2()   { OperationStack::LoadB2();  }
	void LoadByte3()   { OperationStack::LoadB3();  }
	void LoadHWord0()  { OperationStack::LoadH0();  }
	void LoadHWord2()  { OperationStack::LoadH2();  }
	void LoadWord()    { OperationStack::LoadW();   }
	void LoadDWord()   { OperationStack::LoadD();   }
	void StoreByte0()  { OperationStack::StoreB0(); }
	void StoreByte1()  { OperationStack::StoreB1(); }
	void StoreByte2()  { OperationStack::StoreB2(); }
	void StoreByte3()  { OperationStack::StoreB3(); }
	void StoreHWord0() { OperationStack::StoreH0(); }
	void StoreHWord2() { OperationStack::StoreH2(); }
	void StoreWord()   { OperationStack::StoreW();  }
	void StoreDWord()  { OperationStack::StoreD();  }
#pragma endregion
	#pragma region Aritmetics
	void AddI32() { OperationStack::AddI32(); }
	void AddI64() { OperationStack::AddI64(); }
	void AddF32() { OperationStack::AddF32(); }
	void AddF64() { OperationStack::AddF64(); }
	void IncI32() 
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).IValue++;
	}
	void IncI64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).IValue++;
	}
	void IncF32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).FValue++;
	}
	void IncF64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).FValue++;
	}

	void SubI32() { OperationStack::SubI32(); }
	void SubI64() { OperationStack::SubI64(); }
	void SubF32() { OperationStack::SubF32(); }
	void SubF64() { OperationStack::SubF64(); }
	void DecI32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).IValue--;
	}
	void DecI64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).IValue--;
	}
	void DecF32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).FValue--;
	}
	void DecF64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).FValue--;
	}

	void MulI32() { OperationStack::MulI32(); }
	void MulI64() { OperationStack::MulI64(); }
	void MulU32() { OperationStack::MulU32(); }
	void MulU64() { OperationStack::MulU64(); }
	void MulF32() { OperationStack::MulF32(); }
	void MulF64() { OperationStack::MulF64(); }

	void DivI32() { OperationStack::DivI32(); }
	void DivI64() { OperationStack::DivI64(); }
	void DivU32() { OperationStack::DivU32(); }
	void DivU64() { OperationStack::DivU64(); }
	void DivF32() { OperationStack::DivF32(); }
	void DivF64() { OperationStack::DivF64(); }

	void ModI32() { OperationStack::ModI32(); }
	void ModU32() { OperationStack::ModI64(); }
	void ModI64() { OperationStack::ModU32(); }
	void ModU64() { OperationStack::ModU64(); }
	void ModF32() { OperationStack::ModF32(); }
	void ModF64() { OperationStack::ModF64(); }

	void NegI32() { OperationStack::NegI32(); }
	void NegI64() { OperationStack::NegI64(); }
	void NegF32() { OperationStack::NegF32(); }
	void NegF64() { OperationStack::NegF64(); }
#pragma endregion
	#pragma region Bitwise
	void AndWord()  { OperationStack::AndW();   }
	void AndDWord() { OperationStack::AndW();   }
	void OrWord()   { OperationStack::OrW();    }
	void OrDWord()  { OperationStack::OrD();    }
	void XorWord()  { OperationStack::XorW();   }
	void XorDWord() { OperationStack::XorD();   }
	void NotWord()  { OperationStack::NotW();   }
	void NotDWord() { OperationStack::NotD();   }
	void ShlWord()  { OperationStack::ShlW();   }
	void ShlDWord() { OperationStack::ShlD();   }
	void ShrI32()   { OperationStack::ShrI32(); }
	void ShrU32()   { OperationStack::ShrU32(); }
	void ShrI64()   { OperationStack::ShrI64(); }
	void ShrU64()   { OperationStack::ShrU64(); }
#pragma endregion	
	#pragma region Jumps
	inline static void Jump(i16 offset)
	{
		ProgramCounter += offset;
	}
	void Jmp()
	{
		i16 offset = GetNextHWord().IValue;
		Jump(offset);
	}

	void JmpI32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI32())
			Jump(offset);
	}
	void JmpI32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI32())
			Jump(offset);
	}
	void JmpI32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI32())
			Jump(offset);
	}
	void JmpI32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI32())
			Jump(offset);
	}
	void JmpI32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI32())
			Jump(offset);
	}
	void JmpI32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI32())
			Jump(offset);
	}

	void JmpU32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU32())
			Jump(offset);
	}
	void JmpU32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU32())
			Jump(offset);
	}
	void JmpU32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU32())
			Jump(offset);
	}
	void JmpU32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU32())
			Jump(offset);
	}

	void JmpI64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI64())
			Jump(offset);
	}
	void JmpI64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI64())
			Jump(offset);
	}
	void JmpI64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI64())
			Jump(offset);
	}
	void JmpI64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI64())
			Jump(offset);
	}
	void JmpI64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI64())
			Jump(offset);
	}
	void JmpI64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI64())
			Jump(offset);
	}

	void JmpU64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU64())
			Jump(offset);
	}
	void JmpU64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU64())
			Jump(offset);
	}
	void JmpU64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU64())
			Jump(offset);
	}
	void JmpU64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU64())
			Jump(offset);
	}

	void JmpF32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF32())
			Jump(offset);
	}
	void JmpF32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF32())
			Jump(offset);
	}
	void JmpF32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF32())
			Jump(offset);
	}
	void JmpF32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF32())
			Jump(offset);
	}
	void JmpF32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF32())
			Jump(offset);
	}
	void JmpF32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF32())
			Jump(offset);
	}

	void JmpF64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF64())
			Jump(offset);
	}
	void JmpF64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF64())
			Jump(offset);
	}
	void JmpF64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF64())
			Jump(offset);
	}
	void JmpF64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF64())
			Jump(offset);
	}
	void JmpF64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF64())
			Jump(offset);
	}
	void JmpF64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF64())
			Jump(offset);
	}

#pragma endregion	
	#pragma region FunctionCall
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
		default: ASSERT(true, "System call function not implemented!"); break;
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
#pragma endregion
	#pragma region SystemCalls
	void PrintString()
	{
		std::cout << reinterpret_cast<const char*>(OperationStack::TopD().UValue);
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
#pragma endregion
	#pragma region Casts
    void I32ToI64() 
	{ 
		OperationStack::PushW(OperationStack::TopW().IValue < 0 ? 0xffffffff : 0); 
	}
	void I32ToF32() { OperationStack::TopW().FValue = static_cast<f32>(OperationStack::TopW().IValue); }
	void I32ToF64() 
	{ 
		i32 v = OperationStack::TopW().IValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void I64ToI32() { OperationStack::PopW(); }
	void I64ToF32()
	{
		OperationStack::TopW(1).FValue = static_cast<f32>(OperationStack::TopD().IValue);
		OperationStack::PopW();
	}
	void I64ToF64() { OperationStack::TopD().FValue = static_cast<f64>(OperationStack::TopD().IValue); }
	void F32ToI32() { OperationStack::TopW().IValue = static_cast<i32>(OperationStack::TopW().FValue); }
	void F32ToI64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<i64>(v));
	}
	void F32ToF64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void F64ToI32()
	{
		OperationStack::TopW(1).IValue = (i32)OperationStack::TopD().FValue;
		OperationStack::PopW();
	}
	void F64ToI64() { OperationStack::TopD().IValue = static_cast<i64>(OperationStack::TopD().FValue); }
	void F64ToF32()
	{
		f64 v = OperationStack::TopD().FValue; OperationStack::PopW();
		OperationStack::TopW().FValue = static_cast<f32>(v);
	}

#pragma endregion
} // namespace BVM::Machine

#pragma once

namespace BVM::Machine
{
    void Exit();

	void PushByte0();
	void PushByte1();
	void PushByte2();
	void PushByte3();
	void PushHWord0();
	void PushHWord2();
	void PushWord();
	void PushWord0();
	void PushWord1();
	void PushWord2();
	void PushWord3();
	void PushDWord();
	void PushDWord0();
	void PushDWord1();
	void PushDWord2();
	void PushDWord3();
	void PushWords();

	void PushWordValue0();
	void PushDWordValue0();
	void PushI32_1();
	void PushI32_2();
	void PushI64_1();
	void PushI64_2();
	void PushF32_1();
	void PushF32_2();
	void PushF64_1();
	void PushF64_2();

	void PushI8AsI32();
	void PushI8AsI64();
	void PushWordFromPool();
	void PushWordFromPoolWide();
	void PushDWordFromPool();
	void PushDWordFromPoolWide();

	void PopByte0();
	void PopByte1();
	void PopByte2();
	void PopByte3();
	void PopHWord0();
	void PopHWord2();
	void PopWord();
	void PopWord0();
	void PopWord1();
	void PopWord2();
	void PopWord3();
	void PopDWord();
	void PopDWord0();
	void PopDWord1();
	void PopDWord2();
	void PopDWord3();
	void PopWords();

	void DupWord();
	void DupWordX1();
	void DupWordX2();
	void DupDWord();
	void DupDWordX1();
	void DupDWordX2();
	void SwapWord();
	void SwapDWord();

	void GetAddress();
	void LoadByte0();
	void LoadByte1();
	void LoadByte2();
	void LoadByte3();
	void LoadHWord0();
	void LoadHWord2();
	void LoadWord();
	void LoadDWord();
	void StoreByte0();
	void StoreByte1();
	void StoreByte2();
	void StoreByte3();
	void StoreHWord0();
	void StoreHWord2();
	void StoreWord();
	void StoreDWord();

	void AddI32();
	void AddI64();
	void AddF32();
	void AddF64();
	void IncI32();
	void IncI64();
	void IncF32();
	void IncF64();

	void SubI32();
	void SubI64();
	void SubF32();
	void SubF64();
	void DecI32();
	void DecI64();
	void DecF32();
	void DecF64();

	void MulI32();
	void MulU32();
	void MulI64();
	void MulU64();
	void MulF32();
	void MulF64();

	void DivI32();
	void DivU32();
	void DivI64();
	void DivU64();
	void DivF32();
	void DivF64();

	void ModI32();
	void ModU32();
	void ModI64();
	void ModU64();
	void ModF32();
	void ModF64();

	void NegI32();
	void NegI64();
	void NegF32();
	void NegF64();

	void AndWord();
	void AndDWord();
	void OrWord();
	void OrDWord();
	void XorWord();
	void XorDWord();
	void NotWord();
	void NotDWord();
	void ShlWord();
	void ShlDWord();
	void ShrI32();
	void ShrU32();
	void ShrI64();
	void ShrU64();

	void Jmp();

	void JmpI32Eq();
	void JmpI32Ne();
	void JmpI32Gt();
	void JmpI32Lt();
	void JmpI32Ge();
	void JmpI32Le();
	void JmpU32Gt();
	void JmpU32Lt();
	void JmpU32Ge();
	void JmpU32Le();

	void JmpI64Eq();
	void JmpI64Ne();
	void JmpI64Gt();
	void JmpI64Lt();
	void JmpI64Ge();
	void JmpI64Le();
	void JmpU64Gt();
	void JmpU64Lt();
	void JmpU64Ge();
	void JmpU64Le();

	void JmpF32Eq();
	void JmpF32Ne();
	void JmpF32Gt();
	void JmpF32Lt();
	void JmpF32Ge();
	void JmpF32Le();

	void JmpF64Eq();
	void JmpF64Ne();
	void JmpF64Gt();
	void JmpF64Lt();
	void JmpF64Ge();
	void JmpF64Le();

	void Call();
	void SysCall();
	void ReturnVoid();
	void ReturnByte();
	void ReturnHWord();
	void ReturnWord();
	void ReturnDWord();
	void ReturnWords();

	void PrintString();
	void PrintI64();
	void PrintF64();
	void CallSqrtF32();
	void CallSqrtF64();

	void I32ToI64();
	void I32ToF32();
	void I32ToF64();
	void I64ToI32();
	void I64ToF32();
	void I64ToF64();
	void F32ToI32();
	void F32ToI64();
	void F32ToF64();
	void F64ToI32();
	void F64ToI64();
	void F64ToF32();

	typedef void (*OpcodeFunc)();
	constexpr OpcodeFunc OpcodeToFunc[256] =
	{
		Exit,
		PushByte0,
		PushByte1,
		PushByte2,
		PushByte3,
		PushHWord0,
		PushHWord2,
		PushWord,
		PushWord0,
		PushWord1,
		PushWord2,
		PushWord3,
		PushDWord,
		PushDWord0,
		PushDWord1,
		PushDWord2,
		PushDWord3,
		PushWords,

		PushWordValue0,
		PushDWordValue0,
		PushI32_1,
		PushI32_2,
		PushI64_1,
		PushI64_2,
		PushF32_1,
		PushF32_2,
		PushF64_1,
		PushF64_2,

		PushI8AsI32,
		PushI8AsI64,
		PushWordFromPool,
		PushWordFromPoolWide,
		PushDWordFromPool,
		PushDWordFromPoolWide,

		PopByte0,
		PopByte1,
		PopByte2,
		PopByte3,
		PopHWord0,
		PopHWord2,
		PopWord,
		PopWord0,
		PopWord1,
		PopWord2,
		PopWord3,
		PopDWord,
		PopDWord0,
		PopDWord1,
		PopDWord2,
		PopDWord3,
		PopWords,

		DupWord,
		DupWordX1,
		DupWordX2,
		DupDWord,
		DupDWordX1,
		DupDWordX2,
		SwapWord,
		SwapDWord,

		GetAddress,
		LoadByte0,
		LoadByte1,
		LoadByte2,
		LoadByte3,
		LoadHWord0,
		LoadHWord2,
		LoadWord,
		LoadDWord,
		StoreByte0,
		StoreByte1,
		StoreByte2,
		StoreByte3,
		StoreHWord0,
		StoreHWord2,
		StoreWord,
		StoreDWord,

		AddI32,
		AddI64,
		AddF32,
		AddF64,
		IncI32,
		IncI64,
		IncF32,
		IncF64,

		SubI32,
		SubI64,
		SubF32,
		SubF64,
		DecI32,
		DecI64,
		DecF32,
		DecF64,

		MulI32,
		MulU32,
		MulI64,
		MulU64,
		MulF32,
		MulF64,

		DivI32,
		DivU32,
		DivI64,
		DivU64,
		DivF32,
		DivF64,

		ModI32,
		ModU32,
		ModI64,
		ModU64,
		ModF32,
		ModF64,

		NegI32,
		NegI64,
		NegF32,
		NegF64,

		AndWord,
		AndDWord,
		OrWord,
		OrDWord,
		XorWord,
		XorDWord,
		NotWord,
		NotDWord,
		ShlWord,
		ShlDWord,
		ShrI32,
		ShrU32,
		ShrI64,
		ShrU64,

		Jmp,

		JmpI32Eq,
		JmpI32Ne,
		JmpI32Lt,
		JmpI32Gt,
		JmpI32Le,
		JmpI32Ge,

		JmpI64Eq,
		JmpI64Ne,
		JmpI64Lt,
		JmpI64Gt,
		JmpI64Le,
		JmpI64Ge,

		JmpF32Eq,
		JmpF32Ne,
		JmpF32Lt,
		JmpF32Gt,
		JmpF32Le,
		JmpF32Ge,

		JmpF64Eq,
		JmpF64Ne,
		JmpF64Lt,
		JmpF64Gt,
		JmpF64Le,
		JmpF64Ge,

		JmpU32Lt,
		JmpU32Gt,
		JmpU32Le,
		JmpU32Ge,

		JmpU64Lt,
		JmpU64Gt,
		JmpU64Le,
		JmpU64Ge,

		Call,
		nullptr, // call ext
		SysCall,
		ReturnVoid,
		ReturnByte,
		ReturnHWord,
		ReturnWord,
		ReturnDWord,
		ReturnWords,

		I32ToI64,
		I32ToF32,
		I32ToF64,
		I64ToI32,
		I64ToF32,
		I64ToF64,
		F32ToI32,
		F32ToI64,
		F32ToF64,
		F64ToI32,
		F64ToI64,
		F64ToF32
	};
} // namespace BVM::Machine

#pragma once

namespace BVM
{
    typedef void (*InstructionFunc)();
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
	void PushStringFromPool();
	void PushStringFromPoolWide();

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
	void LoadWords();

	void LoadBufferByteVal();
	void LoadBufferHWordVal();
	void LoadBufferWordVal();
	void LoadBufferDWordVal();
	void LoadBufferWordsVal();

	void LoadBufferByteRef();
	void LoadBufferHWordRef();
	void LoadBufferWordRef();
	void LoadBufferDWordRef();
	void LoadBufferWordsRef();

	void LoadOffsetByte0();
	void LoadOffsetByte1();
	void LoadOffsetByte2();
	void LoadOffsetByte3();
	void LoadOffsetHWord0();
	void LoadOffsetHWord2();
	void LoadOffsetWord();
	void LoadOffsetDWord();
	void LoadOffsetWords();

	void StoreByte0();
	void StoreByte1();
	void StoreByte2();
	void StoreByte3();
	void StoreHWord0();
	void StoreHWord2();
	void StoreWord();
	void StoreDWord();
	void StoreWords();

	void StoreBufferByte();
	void StoreBufferHWord();
	void StoreBufferWord();
	void StoreBufferDWord();
	void StoreBufferWords();

	void StoreOffsetByte0();
	void StoreOffsetByte1();
	void StoreOffsetByte2();
	void StoreOffsetByte3();
	void StoreOffsetHWord0();
	void StoreOffsetHWord2();
	void StoreOffsetWord();
	void StoreOffsetDWord();
	void StoreOffsetWords();

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

	void Alloc();
	void Dealloc();
} // namespace BVM::Instructions
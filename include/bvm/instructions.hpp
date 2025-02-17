#pragma once

namespace BVM
{
    typedef void (*InstructionFunc)();
	void NotImplemented();
    void Exit();

	void PushWord();
	void PushWord0();
	void PushWord1();
	void PushWord2();
	void PushWord3();
	void PushWords();

	void PushDWord();
	void PushDWord0();
	void PushDWord1();
	void PushDWord2();
	void PushDWord3();

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

	void PopWord();
	void PopWord0();
	void PopWord1();
	void PopWord2();
	void PopWord3();
	void PopWords();

	void PopDWord();
	void PopDWord0();
	void PopDWord1();
	void PopDWord2();
	void PopDWord3();

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

	void JumpIf();
	void Jmp();

	void Call();
	void SysCall();
	void ReturnVoid();
	void ReturnWord();
	void ReturnDWord();
	void ReturnWords();

	void PrintString();
	void PrintI64();
	void PrintF64();
	void CallSqrtF32();
	void CallSqrtF64();
	void Scan();
	void ScanI64();
	void ScanF64();
	void MemCopy();
	void NanoTime();

	void I32ToI8();
	void I32ToI16();
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

	void CmpEqWord();
	void CmpEqDWord();
	void CmpNeWord();
	void CmpNeDWord();

	void CmpLtI32();
	void CmpGtI32();
	void CmpLeI32();
	void CmpGeI32();

	void CmpLtI64();
	void CmpGtI64();
	void CmpLeI64();
	void CmpGeI64();

	void CmpLtU32();
	void CmpGtU32();
	void CmpLeU32();
	void CmpGeU32();

	void CmpLtU64();
	void CmpGtU64();
	void CmpLeU64();
	void CmpGeU64();

	void CmpLtF32();
	void CmpGtF32();
	void CmpLeF32();
	void CmpGeF32();

	void CmpLtF64();
	void CmpGtF64();
	void CmpLeF64();
	void CmpGeF64();

	void Alloc();
	void Free();
} // namespace BVM::Instructions
#pragma once

#include "types.hpp"

namespace BVM::OperationStack
{
    void Clear();

    Word&  TopW(u32 offset = 0);
    DWord& TopD(u32 offset = 0);
    Word*  TopWs(u32 count);

    void PushW(Word w);
    void PushD(DWord d);
    void PushWs(Word* v, u32 count);

    void PopW();
    void PopD();
    void PopWs(u32 count);

    void OnCall();
    void OnReturn();

    void DupW();
    void DupWX1();
    void DupWX2();
    void DupD();
    void DupDX1();
    void DupDX2();
    void SwapW();
    void SwapD();

    void LoadB(u8 byte_offset);
    void LoadH(u8 hword_offset);
    void LoadW();
    void LoadD();
    void LoadWs(u8 count);

    void LoadBufferByteVal();
    void LoadBufferHWordVal();
    void LoadBufferWordVal();
    void LoadBufferDwordVal();
    void LoadBufferWordsVal(u8 n);

    void LoadBufferByteRef();
    void LoadBufferHWordRef();
    void LoadBufferWordRef();
    void LoadBufferDWordRef();
    void LoadBufferWordsRef(u8 n);

    void LoadOffsetByte(u8 offset, u8 byte);
    void LoadOffsetHWord(u8 offset, u8 hword_index);
    void LoadOffsetWord(u8 offset);
    void LoadOffsetDWord(u8 offset);
    void LoadOffsetWords(u8 offset, u8 n);

    void StoreB(u8 byte_offset);
    void StoreH(u8 hword_offset);
    void StoreW();
    void StoreD();
    void StoreWs(u8 count);

    void StoreBufferByte();
    void StoreBufferHWord();
    void StoreBufferWord();
    void StoreBufferDWord();
    void StoreBufferWords(u8 n);

    void StoreOffsetByte(u8 offset, u8 byte_offset);
    void StoreOffsetHWord(u8 offset, u8 hword_offset);
    void StoreOffsetWord(u8 offset);
    void StoreOffsetDWord(u8 offset);
    void StoreOffsetWords(u8 offset, u8 n);

    void AddI32();
    void AddI64();
    void AddF32();
    void AddF64();

    void SubI32();
    void SubI64();
    void SubF32();
    void SubF64();

    void MulI32();
    void MulI64();
    void MulU32();
    void MulU64();
    void MulF32();
    void MulF64();

    void DivI32();
    void DivI64();
    void DivU32();
    void DivU64();
    void DivF32();
    void DivF64();

    void ModI32();
    void ModI64();
    void ModU32();
    void ModU64();
    void ModF32();
    void ModF64();

    void NegI32();
    void NegI64();
    void NegF32();
    void NegF64();

    void AndW();
    void AndD();
    void OrW();
    void OrD();
    void XorW();
    void XorD();
    void NotW();
    void NotD();
    void ShlW();
    void ShlD();
    void ShrI32();
    void ShrI64();
    void ShrU32();
    void ShrU64();

    bool EqI32();
    bool NeI32();
    bool GtI32();
    bool LtI32();
    bool GeI32();
    bool LeI32();
    
    bool EqF32();
    bool NeF32();
    bool GtF32();
    bool LtF32();
    bool GeF32();
    bool LeF32();

    bool EqI64();
    bool NeI64();
    bool GtI64();
    bool LtI64();
    bool GeI64();
    bool LeI64();

    bool EqF64();
    bool NeF64();
    bool GtF64();
    bool LtF64();
    bool GeF64();
    bool LeF64();

    bool GtU32();
    bool LtU32();
    bool GeU32();
    bool LeU32();

    bool GtU64();
    bool LtU64();
    bool GeU64();
    bool LeU64();

    void Alloc();
    void Dealloc();

    void PrintState();
}

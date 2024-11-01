#pragma once

#include "types.hpp"

namespace BVM::OperationStack
{
    constexpr u32 SIZE = 1 << 20;

    u32 GetBasePointer();
    u32 GetStackPointer();

    void Clear();

    Word& TopW(u32 offset = 0);
    DWord& TopD(u32 offset = 0);
    Word* TopWs(u32 count);

    void PushW(Word w);
    void PushD(DWord d);
    void PushWs(Word* v, u32 count);

    void PopW();
    void PopD();
    void PopWs(u32 count);

    void OnCall();
    void OnReturn(u32 prevBasePointer);

    void DupW();
    void DupWX1();
    void DupWX2();
    void DupD();
    void DupDX1();
    void DupDX2();
    void SwapW();
    void SwapD();

    void LoadB0();
    void LoadB1();
    void LoadB2();
    void LoadB3();
    void LoadH0();
    void LoadH2();
    void LoadW();
    void LoadD();

    void StoreB0();
    void StoreB1();
    void StoreB2();
    void StoreB3();
    void StoreH0();
    void StoreH2();
    void StoreW();
    void StoreD();

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

    void PrintState();
}

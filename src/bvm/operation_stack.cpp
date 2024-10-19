#include <cstring>
#include <cmath>
#include <algorithm>

#include "bvm/operation_stack.hpp"
#include "assertion.hpp"

namespace BVM::OperationStack
{
    Word V[SIZE];
    u32 BasePointer = 0;
    u32 Pointer = 0;

    u32 GetBasePointer() { return BasePointer; }
    u32 GetStackPointer() { return Pointer; }

    void Clear()
    {
        BasePointer = 0;
        Pointer = 0;
    }
#pragma region StackAccess

    Word& TopW(u32 offset)
    {
        u32 idx = Pointer - offset - 1;
        ASSERT(idx < Pointer, "OperationStack index out of range!");
        return V[idx];
    }
    DWord& TopD(u32 offset)
    {
        u32 idx = Pointer - offset - 2;
        ASSERT(idx < Pointer, "OperationStack index out of range!");
        return *reinterpret_cast<DWord*>(V + idx);
    }
    Word* TopWs(u32 count)
    {
        return V + Pointer - count;
    }

    void PushW(Word w)
    {
        V[Pointer++].UValue = w.UValue;
        ASSERT(Pointer < SIZE, "OperationStack overflow");
    }
    void PushD(DWord d)
    {
        DWord& interpreted64 = *reinterpret_cast<DWord*>(V + Pointer);
        interpreted64.UValue = d.UValue;
        Pointer += 2;
        ASSERT(Pointer < SIZE, "OperationStack overflow");
    }
    void PushWs(Word* v, u32 count)
    {
        memcpy(V + Pointer, v, sizeof(Word) * count);
        Pointer += count;
        ASSERT(Pointer < SIZE, "OperationStack overflow");
    }

    void PopW()
    {
        ASSERT(Pointer > BasePointer, "OperationStack underflow");
        --Pointer;
    }
    void PopD()
    {
        ASSERT(Pointer > BasePointer + 1, "OperationStack underflow");
        Pointer -= 2;
    }
    void PopWs(u32 count)
    {
        ASSERT(Pointer >= BasePointer + count, "OperationStack underflow!")
        Pointer -= count;
    }

    void OnCall()
    {
        BasePointer = Pointer;
    }
    void OnReturn(u32 prevBasePointer)
    {
        ASSERT(BasePointer >= prevBasePointer, "OperationStack underflow!");
        Pointer = BasePointer;
        BasePointer = prevBasePointer;
    }

#pragma endregion
#pragma region StackManipulation

    void DupW()
    {
        PushW(TopW(0));
    }
    void DupWX1()
    {
        std::swap(TopW(0), TopW(1));
        PushW(TopW(1));
    }
    void DupWX2()
    {
        std::swap(TopW(1), TopW(2));
        std::swap(TopW(0), TopW(2));
        PushW(TopW(2));
    }
    void DupD()
    {
        PushD(TopD(0));
    }
    void DupDX1()
    {
        std::swap(TopW(0), TopW(2));
        std::swap(TopW(1), TopW(2));
        PushD(TopD(1));
    }
    void DupDX2()
    {
        std::swap(TopD(0), TopD(2));
        PushD(TopD(2));
    }
    void SwapW()
    {
        std::swap(TopW(0), TopW(1));
    }
    void SwapD()
    {
        std::swap(TopD(0), TopD(2));
    }

#pragma endregion
#pragma region Load&Store

    void LoadB0()
    {
        Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB1()
    {
        Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 1U);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB2()
    {
        Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 2U);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB3()
    {
        Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 3U);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadH0()
    {
        HWord* ptr = reinterpret_cast<HWord*>(TopD().UValue);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadH2()
    {
        HWord* ptr = reinterpret_cast<HWord*>(TopD().UValue + 2U);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadW()
    {
        Word* ptr = reinterpret_cast<Word*>(TopD().UValue);
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadD()
    {
        DWord* ptr = reinterpret_cast<DWord*>(TopD().UValue);
        TopD() = ptr->UValue;
    }

    void StoreB0()
    {
        u8 value = TopW().UValue; PopW();
        reinterpret_cast<Byte*>(TopD().UValue)->UValue = value;
        PopD();
    }
    void StoreB1()
    {
        u8 value = TopW().UValue; PopW();
        reinterpret_cast<Byte*>(TopD().UValue + 1U)->UValue = value;
        PopD();
    }
    void StoreB2()
    {
        u8 value = TopW().UValue; PopW();
        reinterpret_cast<Byte*>(TopD().UValue + 2U)->UValue = value;
        PopD();
    }
    void StoreB3()
    {
        u8 value = TopW().UValue; PopW();
        reinterpret_cast<Byte*>(TopD().UValue + 3U)->UValue = value;
        PopD();
    }
    void StoreH0()
    {
        u16 value = TopW().UValue; PopW();
        reinterpret_cast<HWord*>(TopD().UValue)->UValue = value;
        PopD();
    }
    void StoreH2()
    {
        u16 value = TopW().UValue; PopW();
        reinterpret_cast<HWord*>(TopD().UValue + 2U)->UValue = value;
        PopD();
    }
    void StoreW()
    {
        u32 value = TopW().UValue; PopW();
        reinterpret_cast<Word*>(TopD().UValue)->UValue = value;
        PopD();
    }
    void StoreD()
    {
        u64 value = TopD().UValue; PopD();
        reinterpret_cast<DWord*>(TopD().UValue)->UValue = value;
        PopD();
    }
#pragma endregion
#pragma region Aritmetics

    void AddI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue += op;
    }
    void AddI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue += op;
    }
    void AddF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue += op;
    }
    void AddF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue += op;
    }

    void SubI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue -= op;
    }
    void SubI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue -= op;
    }
    void SubF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue -= op;
    }
    void SubF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue -= op;
    }

    void MulI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue *= op;
    }
    void MulI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue *= op;
    }
    void MulU32()
    {
        u32 op = TopW(0).UValue;
        PopW();
        TopW(0).UValue *= op;
    }
    void MulU64()
    {
        u64 op = TopD(0).UValue;
        PopD();
        TopD(0).UValue *= op;
    }
    void MulF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue *= op;
    }
    void MulF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue *= op;
    }

    void DivI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue /= op;
    }
    void DivI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue /= op;
    }
    void DivU32()
    {
        u32 op = TopW(0).UValue;
        PopW();
        TopW(0).UValue /= op;
    }
    void DivU64()
    {
        u64 op = TopD(0).UValue;
        PopD();
        TopD(0).UValue /= op;
    }
    void DivF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue /= op;
    }
    void DivF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue /= op;
    }

    void ModI32()
    {
        i32 op = TopW().IValue;
        PopW();
        TopW().IValue %= op;
    }
    void ModI64()
    {
        i64 op = TopD().IValue;
        PopD();
        TopD().IValue %= op;
    }
    void ModU32()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue %= op;
    }
    void ModU64()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue %= op;
    }
    void ModF32()
    {
        f32 op = TopW().FValue;
        PopW();
        TopW().FValue = fmodf(TopW().FValue, op);
    }
    void ModF64()
    {
        f64 op = TopD().FValue;
        PopD();
        TopD().FValue = fmod(TopD().FValue, op);
    }

    void NegI32()
    {
        TopW().IValue = -TopW().IValue;
    }
    void NegI64()
    {
        TopD().IValue = -TopD().IValue;
    }
    void NegF32()
    {
        TopW().FValue = -TopW().FValue;
    }
    void NegF64()
    {
        TopD().FValue = -TopD().FValue;
    }
#pragma endregion
#pragma region Bitwise

    void AndW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue &= op;
    }
    void AndD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue &= op;
    }
    void OrW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue |= op;
    }
    void OrD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue |= op;
    }
    void XorW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue ^= op;
    }
    void XorD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue ^= op;
    }
    void NotW()
    {
        TopW().UValue = ~TopW().UValue;
    }
    void NotD()
    {
        TopD().UValue = ~TopD().UValue;
    }
    void ShlW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue <<= op;
    }
    void ShlD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue <<= op;
    }
    void ShrI32()
    {
        i32 op = TopW().IValue;
        PopW();
        TopW().IValue >>= op;
    }
    void ShrI64()
    {
        i64 op = TopD().IValue;
        PopD();
        TopD().IValue >>= op;
    }
    void ShrU32()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue >>= op;
    }
    void ShrU64()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue >>= op;
    }
#pragma endregion
#pragma region Comparisons

    bool EqI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a == b;
    }
    bool NeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a != b;
    }
    bool GtI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a > b;
    }
    bool LtI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a < b;
    }
    bool GeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a >= b;
    }
    bool LeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a <= b;
    }
    
    bool EqF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a == b;
    }
    bool NeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a != b;
    }
    bool GtF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a > b;
    }
    bool LtF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a < b;
    }
    bool GeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a >= b;
    }
    bool LeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a <= b;
    }

    bool EqI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a == b;
    }
    bool NeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a != b;
    }
    bool GtI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a > b;
    }
    bool LtI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a < b;
    }
    bool GeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a >= b;
    }
    bool LeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a <= b;
    }

    bool EqF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a == b;
    }
    bool NeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a != b;
    }
    bool GtF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a > b;
    }
    bool LtF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a < b;
    }
    bool GeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a >= b;
    }
    bool LeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a <= b;
    }

    bool GtU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a > b;
    }
    bool LtU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a < b;
    }
    bool GeU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a >= b;
    }
    bool LeU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a <= b;
    }

    bool GtU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a > b;
    }
    bool LtU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a < b;
    }
    bool GeU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a >= b;
    }
    bool LeU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a <= b;
    }
#pragma endregion

    void PrintState()
    {
        for (u32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
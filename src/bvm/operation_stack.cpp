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
        Byte* ptr = TopD().BPointer;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB1()
    {
        Byte* ptr = TopD().BPointer + 1U;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB2()
    {
        Byte* ptr = TopD().BPointer + 2U;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadB3()
    {
        Byte* ptr = TopD().BPointer + 3U;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadH0()
    {
        HWord* ptr = TopD().HPointer;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadH2()
    {
        HWord* ptr = TopD().HPointer + 2U;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadW()
    {
        Word* ptr = TopD().WPointer;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadD()
    {
        DWord* ptr = TopD().DPointer;
        TopD() = ptr->UValue;
    }
    void LoadWs(u8 count)
    {
        Word* ptr = TopD().WPointer;
        PushWs(ptr, count);
    }
    void LoadBufferByteVal()
    {
        u32 index = TopW().UValue;
        Byte* buffer = TopD(1).BPointer;
        PopWs(3);
        
        PushW(buffer[index]);
    }
    void LoadBufferHWordVal()
    {
        u32 index = TopW().UValue;
        HWord* buffer = TopD(1).HPointer;
        PopWs(3);
        
        PushW(buffer[index]);
    }
    void LoadBufferWordVal()
    {
        u32 index = TopW().UValue;
        Word* buffer = TopD(1).WPointer;
        PopWs(3);

        PushW(buffer[index]);
    }
    void LoadBufferDwordVal()
    {
        u32 index = TopW().UValue;
        DWord* buffer = TopD(1).DPointer;
        PopWs(3);

        PushD(buffer[index]);
    }
    void LoadBufferWordsVal(u8 n)
    {
        u32 index = TopW().UValue;
        Word* buffer = TopD(1).WPointer;
        PopWs(3);

        PushWs(buffer + index * n, n);
    }
    void LoadBufferByteRef()
    {
        u32 index = TopW().UValue;
        Byte* buffer = TopD(1).BPointer;

        TopD(1).Pointer = buffer + index;
        PopW();
    }
    void LoadBufferHWordRef()
    {
        u32 index = TopW().UValue;
        HWord* buffer = TopD(1).HPointer;

        TopD(1).Pointer = buffer + index;
        PopW();
    }
    void LoadBufferWordRef()
    {
        u32 index = TopW().UValue;
        Word* buffer = TopD(1).WPointer;

        TopD(1).Pointer = buffer + index;
        PopW();
    }
    void LoadBufferDWordRef()
    {
        u32 index = TopW().UValue;
        DWord* buffer = TopD(1).DPointer;

        TopD(1).Pointer = buffer + index;
        PopW();
    }
    void LoadBufferWordsRef(u8 n)
    {
        u32 index = TopW().UValue;
        Word* buffer = TopD(1).WPointer;

        TopD(1).Pointer = buffer + index * n;
        PopW();
    }
    void LoadOffsetByte0(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value0.B.Value0.UValue;
    }
    void LoadOffsetByte1(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value0.B.Value1.UValue;
    }
    void LoadOffsetByte2(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value1.B.Value0.UValue;
    }
    void LoadOffsetByte3(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value1.B.Value1.UValue;
    }
    void LoadOffsetHWord0(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value0.UValue;
    }
    void LoadOffsetHWord2(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->H.Value1.UValue;
    }
    void LoadOffsetWord(u8 offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadOffsetDWord(u8 offset)
    {
        DWord* ptr = (DWord*)(TopD().WPointer + offset);
        TopD() = ptr->UValue;
    }
    void LoadOffsetWords(u8 offset, u8 n)
    {
        Word* ptr = TopD().WPointer + offset;
        PushWs(ptr, n);
    }
    void StoreB0()
    {
        u8 value = TopW().UValue;
        TopD(1).BPointer->UValue = value;
        PopWs(3);
    }
    void StoreB1()
    {
        u8 value = TopW().UValue;
        Byte* byte = TopD(1).BPointer + 1U;
        byte->UValue = value;
        PopWs(3);
    }
    void StoreB2()
    {
        u8 value = TopW().UValue;
        Byte* byte = TopD(1).BPointer + 2U;
        byte->UValue = value;
        PopWs(3);
    }
    void StoreB3()
    {
        u8 value = TopW().UValue;
        Byte* byte = TopD(1).BPointer + 3U;
        byte->UValue = value;
        PopWs(3);
    }
    void StoreH0()
    {
        u16 value = TopW().UValue;
        TopD(1).HPointer->UValue = value;
    }
    void StoreH2()
    {
        u16 value = TopW().UValue;
        HWord* hword = TopD(1).HPointer + 2U;
        hword->UValue = value;
        PopWs(3);
    }
    void StoreW()
    {
        u32 value = TopW().UValue;
        TopD(1).WPointer->UValue = value;
        PopWs(3);
    }
    void StoreD()
    {
        u64 value = TopD().UValue;
        TopD(2).DPointer->UValue = value;
        PopWs(4);
    }
    void StoreWs(u8 count)
    {
        Word* ws = TopWs(count);
        memcpy(TopD(count).Pointer, ws, sizeof(Word) * count);
        PopWs(count + 2);
    }
    void StoreBufferByte()
    {
        u8 value  = TopW().UValue;
        u32 index = TopW(1).UValue;
        Byte* buffer = TopD(2).BPointer;
        buffer[index].UValue = value;        
        PopWs(4);
    }
    void StoreBufferHWord()
    {
        u16 value = TopW().UValue;
        u32 index = TopW(1).UValue;
        HWord* buffer = TopD(2).HPointer;
        buffer[index] = value;
        PopWs(4);
    }
    void StoreBufferWord()
    {
        u32 value = TopW().UValue;
        u32 index = TopW(1).UValue;
        Word* buffer = TopD(2).WPointer;
        buffer[index] = value;
        PopWs(4);
    }
    void StoreBufferDWord()
    {
        u64 value = TopD().UValue;
        u32 index = TopW(2).UValue;
        DWord* buffer = TopD(3).DPointer;
        buffer[index] = value;
        PopWs(5);
    }
    void StoreBufferWords(u8 n)
    {
        Word* ws = TopWs(n);
        u32 index = TopW(n).UValue;
        Word* buffer = TopD(n + 1).WPointer;
        memcpy(buffer + index * n, ws, sizeof(Word) * n);
        PopWs(n + 3);
    }
    void StoreOffsetByte0(u8 offset)
    {
        u8 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value0.B.Value0.UValue = value;
        PopWs(3);
    }
    void StoreOffsetByte1(u8 offset)
    {
        u8 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value0.B.Value1.UValue = value;
        PopWs(3);
    }
    void StoreOffsetByte2(u8 offset)
    {
        u8 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value1.B.Value0.UValue = value;
        PopWs(3);
    }
    void StoreOffsetByte3(u8 offset)
    {
        u8 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value1.B.Value1.UValue = value;
        PopWs(3);
    }
    void StoreOffsetHWord0(u8 offset)
    {
        u16 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value0.UValue = value;
        PopWs(3);
    }
    void StoreOffsetHWord2(u8 offset)
    {
        u16 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->H.Value1.UValue = value;
        PopWs(3);
    }
    void StoreOffsetWord(u8 offset)
    {
        u32 value = TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ptr->UValue = value;
        PopWs(3);
    }
    void StoreOffsetDWord(u8 offset)
    {
        u64 value = TopD().UValue;
        DWord* ptr = (DWord*)(TopD(2).WPointer + offset);
        ptr->UValue = value;
        PopWs(4);
    }
    void StoreOffsetWords(u8 offset, u8 n)
    {
        Word* ws = TopWs(n);
        Word* ptr = TopD(n).WPointer + offset;
        memcpy(ptr, ws, sizeof(Word) * n);
        PopWs(n + 2);
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

    void Alloc()
    {
        u32 count = TopW().UValue; PopW();
        void* buffer = new Byte[count];
        PushD(buffer);
    }
    void Dealloc()
    {
        Byte* buffer = static_cast<Byte*>(TopD().Pointer);
        delete[] buffer;
        PopD();
    }

    void PrintState()
    {
        for (u32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
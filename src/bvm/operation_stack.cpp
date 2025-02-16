#include "std.hpp"
#include "bvm/operation_stack.hpp"
#include "assertion.hpp"

namespace BVM::OperationStack
{
    constexpr i32 SIZE = 1 << 20;
    Word V[SIZE];
    i32 BasePointer = 0;
    i32 Pointer = 0;

    void Clear()
    {
        BasePointer = 0;
        Pointer = 0;
    }

    Word& TopW(u32 offset)
    {
        i32 idx = Pointer - offset - 1;
        ASSERT(idx >= BasePointer, "OperationStack index out of range!");
        return V[idx];
    }
    DWord& TopD(u32 offset)
    {
        i32 idx = Pointer - offset - 2;
        ASSERT(idx >= BasePointer, "OperationStack index out of range!");
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
        ASSERT(Pointer >= (i32)(BasePointer + count), "OperationStack underflow!")
        Pointer -= count;
    }

    void OnCall()
    {
        V[Pointer].IValue = BasePointer;
        BasePointer = Pointer;
        ++Pointer;
    }
    void OnReturn()
    {
        Pointer = BasePointer;
        BasePointer = V[BasePointer].IValue;
    }

    void PrintState()
    {
        for (i32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
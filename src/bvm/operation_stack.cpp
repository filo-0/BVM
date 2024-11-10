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

    u32 GetBasePointer()  { return BasePointer; }
    u32 GetStackPointer() { return Pointer;     }

    void Clear()
    {
        BasePointer = 0;
        Pointer = 0;
    }

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

    void PrintState()
    {
        for (u32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
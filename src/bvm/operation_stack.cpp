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

    Word TopW(u32 offset)
    {
        i32 idx = Pointer - offset - 1;
        ASSERT(idx >= BasePointer, "OperationStack index out of range!");
        return V[idx];
    }
    DWord TopD(u32 offset)
    {
        i32 idx = Pointer - offset - 2;
        ASSERT(idx >= BasePointer, "OperationStack index out of range!");
        DWord ret;
        ret.WValue[0] = V[idx + 0];
        ret.WValue[1] = V[idx + 1];
        return ret;
    }
    Word* TopWs(u32 count)
    {
        return V + Pointer - count;
    }

    void SwpW(u32 offsetA, u32 offsetB)
    {
        i32 idxA = Pointer - offsetA - 1;
        i32 idxB = Pointer - offsetB - 1;
        ASSERT(idxA >= BasePointer && idxB >= BasePointer, "OperationStack index out of range!");
        Word tmp = V[idxA];
        V[idxA] = V[idxB];
        V[idxB] = tmp;
    }
    void SwpD(u32 offsetA, u32 offsetB)
    {
        i32 idxA = Pointer - offsetA - 2;
        i32 idxB = Pointer - offsetB - 2;
        ASSERT(idxA >= BasePointer && idxB >= BasePointer, "OperationStack index out of range!");
        DWord tmp;
        tmp.WValue[0] = V[idxA + 0];
        tmp.WValue[1] = V[idxB + 1];
        V[idxA + 0] = V[idxB + 0];
        V[idxA + 1] = V[idxB + 1];  
        V[idxB + 0] = tmp.WValue[0];
        V[idxB + 1] = tmp.WValue[1];
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
#include "std.hpp"
#include "bvm/operation_stack.hpp"
#include "bvm/stack.hpp"
#include "assertion.hpp"

namespace BVM::OperationStack
{
    static Word* Pointer;
    void SetPointer(Word* pointer) { Pointer = pointer; }
    #ifdef _DEBUG
    static Word* Bottom;
    static Word* Top;
    void SetBounds(Word* bottom, Word* top)
    {
        Bottom = bottom;
        Top = top;
    }
    #endif

    Word TopW(u32 offset)
    {
        ASSERT(Pointer - offset >= Bottom, "Accessing stack out of bounds!");
        return *(Pointer - offset - 1);
    }
    DWord TopD(u32 offset)
    {
        ASSERT(Pointer - offset - 1 >= Bottom, "Accessing stack out of bounds!");
        DWord ret;
        ret.WValue[0] = *(Pointer - offset - 2);
        ret.WValue[1] = *(Pointer - offset - 1);
        return ret;
    }
    Word* TopWs(u32 count)
    {
        ASSERT(Pointer - count >= Bottom, "Accessing stack out of bounds!");
        return Pointer - count;
    }

    void SwpW(u32 offsetA, u32 offsetB)
    {
        ASSERT(Pointer - offsetA - 1 >= Bottom && Pointer - offsetB - 1 >= Bottom, "Accessing stack out of bounds!");
        std::swap(*(Pointer - offsetA - 1), *(Pointer - offsetB - 1));
    }
    void SwpD(u32 offsetA, u32 offsetB)
    {
        ASSERT(Pointer - offsetA - 2 >= Bottom && Pointer - offsetB - 2 >= Bottom, "Accessing stack out of bounds!");
        std::swap(*(Pointer - offsetA - 2), *(Pointer - offsetB - 2));
        std::swap(*(Pointer - offsetA - 1), *(Pointer - offsetB - 1));
    }

    void PushW(Word w)
    {
        ASSERT(Pointer < Top, "Accessing stack out of bounds!");
        *Pointer = w;
        ++Pointer;
    }
    void PushD(DWord d)
    {
        ASSERT(Pointer + 1 < Top, "Accessing stack out of bounds!");
        Pointer[0] = d.WValue[0];
        Pointer[1] = d.WValue[1];
        Pointer += 2;
    }
    void PushWs(Word* v, u32 count)
    {
        ASSERT(Pointer + count < Top, "Accessing stack out of bounds!");
        for(u32 i = 0; i < count; i++)
            Pointer[i] = v[i];
        Pointer += count;
    }

    void PopW()
    {
        ASSERT(Pointer >= Bottom, "Stack is empty!");
        --Pointer;
    }
    void PopD()
    {
        ASSERT(Pointer + 1 >= Bottom, "Stack is empty!");
        Pointer -= 2;
    }
    void PopWs(u32 count)
    {
        ASSERT(Pointer + count - 1 >= Bottom, "Stack is empty!");
        Pointer -= count;
    }
}
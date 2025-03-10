#include "bvm/function_scope.hpp"
#include "assertion.hpp"

namespace BVM::FunctionScope
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

    DWord GetLocalD(u8 index)   
    { 
        ASSERT(Pointer + index + 1 < Top, "Accessing local variable out of bounds!");
        DWord ret;
        ret.WValue[0] = *(Pointer + index + 0);     
        ret.WValue[1] = *(Pointer + index + 1);
        return ret;
    }
    Word  GetLocalW(u8 index)  
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        return *(Pointer + index);                             
    }
    HWord GetLocalH(u8 index, u8 hword)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        return (Pointer + index)->HValue[hword];
    }
    Byte  GetLocalB(u8 index, u8 byte)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        return (Pointer + index)->BValue[byte];
    }
    Word* GetLocalRef(u8 index)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        return Pointer + index;   
    }

    void SetLocalD(u8 index, DWord val)
    {
        ASSERT(Pointer + index + 1 < Top, "Accessing local variable out of bounds!");
        Pointer[index + 0] = val.WValue[0];
        Pointer[index + 1] = val.WValue[1];
    }
    void SetLocalW(u8 index, Word val)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        Pointer[index] = val;
    }  
    void SetLocalB(u8 index, u8 byte, Byte val)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        Pointer[index].BValue[byte] = val;
    }
    void SetLocalH(u8 index, u8 hword, HWord val)
    {
        ASSERT(Pointer + index < Top, "Accessing local variable out of bounds!");
        Pointer[index].HValue[hword] = val;
    }
}
#include <cstring>

#include "bvm/function_stack.hpp"
#include "assertion.hpp"

namespace BVM::FunctionStack
{
    Word V[SIZE] = {};
    u32 BasePointer = 0;
    u32 Pointer = 0;

    u32 GetBasePointer() { return BasePointer; }
    HWord& GlobalH0(u32 offset) { return V[offset].H.Value0; }
    HWord& GlobalH1(u32 offset) { return V[offset].H.Value1; }

    DWord& LocalD(u8 index)   
    { 
        ASSERT(BasePointer + index + 2 <= Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return *reinterpret_cast<DWord*>(V + BasePointer + index);     
    }
    Word&  LocalW(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index];                             
    }
    HWord& LocalH0(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value0;                    
    }
    HWord& LocalH2(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value1;                    
    }
    Byte&  LocalB0(u8 index)  
    {
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value0.B.Value0;           
    }
    Byte&  LocalB1(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value0.B.Value1;           
    }
    Byte&  LocalB2(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value1.B.Value0;           
    }
    Byte&  LocalB3(u8 index)  
    { 
        ASSERT(BasePointer + index < Pointer, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[BasePointer + index].H.Value1.B.Value1;           
    }

    void PushData(Word* data, u8 count)
    {
        ASSERT(Pointer + count < SIZE && (data || (!data && count == 0)), "FunctionStack overflow!");
        memcpy(V + Pointer, data, sizeof(Word) * count);
    }
    void OnCall(u8 localsCount)
    {
        ASSERT(Pointer + localsCount < SIZE, "FunctionStack overflow!");
        BasePointer = Pointer;
        Pointer += localsCount;
    }
    void OnReturn(u32 PrevBasePointer)
    {
        ASSERT(BasePointer >= PrevBasePointer, "FunctionStack underflow!");
        Pointer = BasePointer;
        BasePointer = PrevBasePointer;
    }

    void PrintState()
    {
        LOG("\n");
        for (u32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
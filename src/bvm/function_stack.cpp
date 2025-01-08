#include "bvm/function_stack.hpp"
#include "assertion.hpp"

namespace BVM::FunctionStack
{
    Word V[SIZE] = {};
    i32 Pointer = SIZE - 1;
    constexpr u32 PREV_STACK_POINTER_OFFSET = 0;
    constexpr u32 PREV_PROGRAM_COUNTER_OFFSET = 1;
    constexpr u32 LOCAL_OFFSET = 2;

    DWord& LocalD(u8 index)   
    { 
        ASSERT(Pointer + index + LOCAL_OFFSET < SIZE, "Accessed FStack local var outside of the scope [local=%d]", index);
        return *reinterpret_cast<DWord*>(V + Pointer + index + LOCAL_OFFSET);     
    }
    Word&  LocalW(u8 index)  
    { 
        ASSERT(Pointer + index + LOCAL_OFFSET < SIZE, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[Pointer + index + LOCAL_OFFSET];                             
    }
    HWord& LocalH(u8 index, u8 hword_offset)  
    { 
        ASSERT(hword_offset < 2, "Hword offset out of range!");
        ASSERT(Pointer + index + LOCAL_OFFSET < SIZE, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[Pointer + index + LOCAL_OFFSET].HValue[hword_offset];                    
    }
    Byte&  LocalB(u8 index, u8 byte_offset)  
    {
        ASSERT(byte_offset < 4, "Hword offset out of range!");
        ASSERT(Pointer + index + LOCAL_OFFSET < SIZE, "Accessed FStack local var outside of the scope [local=%d]", index);
        return V[Pointer + index + LOCAL_OFFSET].BValue[byte_offset];           
    }

    void PushData(Word* data, u8 count)
    {
        ASSERT(Pointer + LOCAL_OFFSET + count < SIZE, "FunctionStack overflow!");
        memcpy(V + Pointer + LOCAL_OFFSET, data, sizeof(Word) * count);
    }
    void OnCall(u32 programCounter, u8 localsCount)
    {
        ASSERT((i32)(Pointer - localsCount - LOCAL_OFFSET) > 0, "FunctionStack overflow!");
        i32 prevPointer = Pointer;
        Pointer -= localsCount + LOCAL_OFFSET;
        V[Pointer + PREV_STACK_POINTER_OFFSET].IValue = prevPointer;
        V[Pointer + PREV_PROGRAM_COUNTER_OFFSET].UValue = programCounter;
    }
    u32 OnReturn()
    {
        ASSERT(V[Pointer].UValue <= SIZE, "FunctionStack underflow!");

        i32 prevProgramCounter = V[Pointer + PREV_PROGRAM_COUNTER_OFFSET].IValue; 
        Pointer = V[Pointer + PREV_STACK_POINTER_OFFSET].UValue;
        return prevProgramCounter;
    }   

    void PrintState()
    {
        LOG("\n");
        for (i32 i = 0; i < Pointer; i++)
        {
            LOG("0x%08X\n", V[i].UValue);
        }
    }
}
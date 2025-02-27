#include "bvm/stack.hpp"
#include "bvm/operation_stack.hpp"
#include "bvm/function_scope.hpp"

namespace BVM::Stack
{
    static u32 StackSize = 0;
    static u32 Pointer = 0;
    static Word* Data;

    void SetDataBlock(Word* data, u32 size)
    {
        Data = data;
        StackSize = size;
        Pointer = StackSize - 1;
    }

    constexpr u32 PC_OFFSET = 0;
    constexpr u32 SP_OFFSET = 1;
    constexpr u32 OSP_OFFSET = 2;
    constexpr u32 LOCAL_OFFSET = 3;

    /*
    STACK_SCOPE
    {
        Stack wn
        ...
        Stack w1
        Stack w0 <- SP
        Local wn
        ...
        Local w1
        Local w0 <- LocalPointer
        OStackPointer
        Pointer
        ProgramCounter
    }
    */
    void PushScope(const Word* args, u8 argWordCount, u8 localWordCount, u16 stackWordCount, u32 programCounter)
    {
        u32 prevPointer = Pointer;
        Pointer -= localWordCount + stackWordCount + LOCAL_OFFSET;
        if(Pointer >= StackSize)
        {
            std::cout << "Stack overflow\n";
            exit(1);
        }

        Data[Pointer + PC_OFFSET] = programCounter;
        Data[Pointer + SP_OFFSET] = prevPointer;
        Data[Pointer + OSP_OFFSET] = Pointer + LOCAL_OFFSET + localWordCount;
        for (size_t i = 0; i < argWordCount; i++)
            Data[Pointer + LOCAL_OFFSET + i] = args[i];
        FunctionScope::SetPointer(Data + Pointer + LOCAL_OFFSET);
        OperationStack::SetPointer(Data + Pointer + LOCAL_OFFSET + localWordCount);
        #ifdef _DEBUG
        Word* localBottom = Data + Pointer + LOCAL_OFFSET;
        Word* localTop = Data + Pointer + LOCAL_OFFSET + localWordCount;
        Word* stackTop = Data + Pointer + LOCAL_OFFSET + localWordCount + stackWordCount;
        FunctionScope::SetBounds(localBottom, localTop);
        OperationStack::SetBounds(localTop, stackTop);
        #endif
    }

    u32 PopScope()
    {
        u32 pc  = Data[Pointer + PC_OFFSET].UValue;
        Pointer = Data[Pointer + SP_OFFSET].UValue;

        u32 ostackPointer = Data[Pointer + OSP_OFFSET].UValue;
        FunctionScope::SetPointer(Data + Pointer + LOCAL_OFFSET);
        OperationStack::SetPointer(Data + ostackPointer);

        #ifdef _DEBUG
        Word* localBottom = Data + Pointer + LOCAL_OFFSET;
        Word* localTop = Data + ostackPointer;
        Word* stackTop = Data + Data[Pointer + SP_OFFSET].UValue; // previous stack pointer
        FunctionScope::SetBounds(localBottom, localTop);
        OperationStack::SetBounds(localTop, stackTop);
        #endif
        return pc;
    }
} // namespace BVM::Stack
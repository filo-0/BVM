#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void LoadB(u8 byte_offset)
    {
        Byte* ptr = TopD().BPointer + byte_offset;
        PopW();
        TopW() = ptr->UValue;
    }
    void LoadH(u8 hword_offset)
    {
        HWord* ptr = TopD().HPointer + hword_offset;
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
    void LoadOffsetByte(u8 offset, u8 byte_offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW().UValue = ((Byte*)ptr + byte_offset)->UValue;
    }
    void LoadOffsetHWord(u8 offset, u8 hword_offset)
    {
        Word* ptr = TopD().WPointer + offset;
        PopW();
        TopW() = ((HWord*)ptr + hword_offset)->UValue;
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
} // namespace BVM::OperationStack

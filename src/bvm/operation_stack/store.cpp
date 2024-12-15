#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void StoreB(u8 byte_offset)
    {
        u8 value = (u8)TopW().UValue;
        Byte* ptr = TopD(1).BPointer + byte_offset;
        ptr->UValue = value;
        PopWs(3);
    }
    void StoreH(u8 hword_offset)
    {
        u16 value = (u16)TopW().UValue;
        HWord* ptr = TopD(1).HPointer + hword_offset;
        ptr->UValue = value;
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
        u8 value  = (u8)TopW().UValue;
        u32 index = TopW(1).UValue;
        Byte* buffer = TopD(2).BPointer;
        buffer[index].UValue = value;        
        PopWs(4);
    }
    void StoreBufferHWord()
    {
        u16 value = (u16)TopW().UValue;
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
    void StoreOffsetByte(u8 offset, u8 byte_offset)
    {
        u8 value = (u8)TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ((Byte*) ptr + byte_offset)->UValue = value;
        PopWs(3);
    }
    void StoreOffsetHWord(u8 offset, u8 hword_offset)
    {
        u16 value = (u16)TopW().UValue;
        Word* ptr = TopD(1).WPointer + offset;
        ((HWord*)ptr + hword_offset)->UValue = value;
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
} // namespace BVM

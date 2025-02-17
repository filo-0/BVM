#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void AndW()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a & b);
    }
    void AndD()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a & b);
    }
    void OrW()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a | b);
    }
    void OrD()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a | b);
    }
    void XorW()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a ^ b);
    }
    void XorD()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a ^ b);
    }
    void NotW()
    {
        u32 n = ~TopW().UValue;
        PopW();
        PushW(n);
    }
    void NotD()
    {
        u64 n = ~TopD().UValue;
        PopD();
        PushD(n);
    }
    void ShlW()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a << b);
    }
    void ShlD()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a << b);
    }
    void ShrI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a >> b);
    }
    void ShrI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a >> b);
    }
    void ShrU32()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a >> b);
    }
    void ShrU64()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a >> b);
    }
} // namespace BVM::OperationStack

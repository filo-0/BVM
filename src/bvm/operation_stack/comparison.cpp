#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void CmpEqW()
    {
        Word a = TopW();
        Word b = TopW(1);
        PopD();
        PushW(a.UValue == b.UValue);
    }
    void CmpEqD()
    {
        DWord a = TopD(); 
        DWord b = TopD(2);
        PopWs(4);
        PushW(a.UValue == b.UValue);
    }
    void CmpNeW()
    {
        Word a = TopW();
        Word b = TopW(1);
        PopD();
        PushW(a.UValue != b.UValue);
    }
    void CmpNeD()
    {
        DWord a = TopD();
        DWord b = TopD(2);
        PopWs(4);
        PushW(a.UValue != b.UValue);
    }
    
    void CmpLtI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a < b);
    }
    void CmpGtI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a > b);
    }
    void CmpLeI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a <= b);
    }
    void CmpGeI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a >= b);
    }

    void CmpLtI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpGtI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a > b);
    }
    void CmpLeI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a <= b);
    }
    void CmpGeI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a >= b);
    }

    void CmpLtU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a < b);
    }
    void CmpGtU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a > b);
    }
    void CmpLeU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a <= b);
    }
    void CmpGeU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a >= b);
    }

    void CmpLtU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpGtU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a > b);
    }
    void CmpLeU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a <= b);
    }
    void CmpGeU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a >= b);
    }

    void CmpLtF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a < b);
    }
    void CmpGtF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a > b);
    }
    void CmpLeF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a <= b);
    }
    void CmpGeF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a >= b);
    }

    void CmpLtF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpGtF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a > b);
    }
    void CmpLeF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a <= b);
    }
    void CmpGeF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a >= b);
    }
} // namespace BVM::OperationStack

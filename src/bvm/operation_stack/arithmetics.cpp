#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void AddI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a + b);
    }
    void AddI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a + b);
    }
    void AddF32()
    {
        f32 b = TopW(0).FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a + b);
    }
    void AddF64()
    {
        f64 b = TopD(0).FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushD(a + b);
    }

    void SubI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a - b);
    }
    void SubI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a - b);
    }
    void SubF32()
    {
        f32 b = TopW(0).FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a - b);
    }
    void SubF64()
    {
        f64 b = TopD(0).FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushD(a - b);
    }

    void MulI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a * b);
    }
    void MulI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a * b);
    }
    void MulU32()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a * b);
    }
    void MulU64()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a * b);
    }
    void MulF32()
    {
        f32 b = TopW(0).FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a * b);
    }
    void MulF64()
    {
        f64 b = TopD(0).FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushD(a * b);
    }

    void DivI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a / b);
    }
    void DivI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a / b);
    }
    void DivU32()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a / b);
    }
    void DivU64()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a / b);
    }
    void DivF32()
    {
        f32 b = TopW(0).FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a / b);
    }
    void DivF64()
    {
        f64 b = TopD(0).FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushD(a / b);
    }

    void ModI32()
    {
        i32 b = TopW(0).IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a % b);
    }
    void ModI64()
    {
        i64 b = TopD(0).IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushD(a % b);
    }
    void ModU32()
    {
        u32 b = TopW(0).UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a % b);
    }
    void ModU64()
    {
        u64 b = TopD(0).UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushD(a % b);
    }
    void ModF32()
    {
        f32 b = TopW(0).FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(fmodf(a, b));
    }
    void ModF64()
    {
        f64 b = TopD(0).FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushD(fmod(a, b));
    }

    void NegI32()
    {
        i32 neg = -TopW().IValue;
        PopW();
        PushW(neg);
    }
    void NegI64()
    {
        i64 neg = -TopD().IValue;
        PopD();
        PushD(neg);
    }
    void NegF32()
    {
        f32 neg = -TopW().FValue;
        PopW();
        PushW(neg);
    }
    void NegF64()
    {
        f64 neg = -TopD().FValue;
        PopD();
        PushD(neg);
    }
} // namespace BVM::OperationStack

#include <cmath>

#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void AddI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue += op;
    }
    void AddI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue += op;
    }
    void AddF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue += op;
    }
    void AddF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue += op;
    }

    void SubI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue -= op;
    }
    void SubI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue -= op;
    }
    void SubF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue -= op;
    }
    void SubF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue -= op;
    }

    void MulI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue *= op;
    }
    void MulI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue *= op;
    }
    void MulU32()
    {
        u32 op = TopW(0).UValue;
        PopW();
        TopW(0).UValue *= op;
    }
    void MulU64()
    {
        u64 op = TopD(0).UValue;
        PopD();
        TopD(0).UValue *= op;
    }
    void MulF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue *= op;
    }
    void MulF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue *= op;
    }

    void DivI32()
    {
        i32 op = TopW(0).IValue;
        PopW();
        TopW(0).IValue /= op;
    }
    void DivI64()
    {
        i64 op = TopD(0).IValue;
        PopD();
        TopD(0).IValue /= op;
    }
    void DivU32()
    {
        u32 op = TopW(0).UValue;
        PopW();
        TopW(0).UValue /= op;
    }
    void DivU64()
    {
        u64 op = TopD(0).UValue;
        PopD();
        TopD(0).UValue /= op;
    }
    void DivF32()
    {
        f32 op = TopW(0).FValue;
        PopW();
        TopW(0).FValue /= op;
    }
    void DivF64()
    {
        f64 op = TopD(0).FValue;
        PopD();
        TopD(0).FValue /= op;
    }

    void ModI32()
    {
        i32 op = TopW().IValue;
        PopW();
        TopW().IValue %= op;
    }
    void ModI64()
    {
        i64 op = TopD().IValue;
        PopD();
        TopD().IValue %= op;
    }
    void ModU32()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue %= op;
    }
    void ModU64()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue %= op;
    }
    void ModF32()
    {
        f32 op = TopW().FValue;
        PopW();
        TopW().FValue = fmodf(TopW().FValue, op);
    }
    void ModF64()
    {
        f64 op = TopD().FValue;
        PopD();
        TopD().FValue = fmod(TopD().FValue, op);
    }

    void NegI32()
    {
        TopW().IValue = -TopW().IValue;
    }
    void NegI64()
    {
        TopD().IValue = -TopD().IValue;
    }
    void NegF32()
    {
        TopW().FValue = -TopW().FValue;
    }
    void NegF64()
    {
        TopD().FValue = -TopD().FValue;
    }
} // namespace BVM::OperationStack

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
    void CmpLtI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a < b);
    }
    void CmpLeI32()
    {
        i32 b = TopW().IValue;
        i32 a = TopW(1).IValue;
        PopD();
        PushW(a <= b);
    }
    void CmpLtI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpLeI64()
    {
        i64 b = TopD().IValue;
        i64 a = TopD(2).IValue;
        PopWs(4);
        PushW(a <= b);
    }
    void CmpLtU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a < b);
    }
    void CmpLeU32()
    {
        u32 b = TopW().UValue;
        u32 a = TopW(1).UValue;
        PopD();
        PushW(a <= b);
    }
    void CmpLtU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpLeU64()
    {
        u64 b = TopD().UValue;
        u64 a = TopD(2).UValue;
        PopWs(4);
        PushW(a <= b);
    }
    void CmpLtF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a < b);
    }
    void CmpLeF32()
    {
        f32 b = TopW().FValue;
        f32 a = TopW(1).FValue;
        PopD();
        PushW(a <= b);
    }
    void CmpLtF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a < b);
    }
    void CmpLeF64()
    {
        f64 b = TopD().FValue;
        f64 a = TopD(2).FValue;
        PopWs(4);
        PushW(a <= b);
    }

    bool EqI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a == b;
    }
    bool NeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a != b;
    }
    bool GtI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a > b;
    }
    bool LtI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a < b;
    }
    bool GeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a >= b;
    }
    bool LeI32()
    {
        i32 b = TopW().IValue; PopW();
        i32 a = TopW().IValue; PopW();
        return a <= b;
    }
    
    bool EqF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a == b;
    }
    bool NeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a != b;
    }
    bool GtF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a > b;
    }
    bool LtF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a < b;
    }
    bool GeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a >= b;
    }
    bool LeF32()
    {
        f32 b = TopW().FValue; PopW();
        f32 a = TopW().FValue; PopW();
        return a <= b;
    }

    bool EqI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a == b;
    }
    bool NeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a != b;
    }
    bool GtI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a > b;
    }
    bool LtI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a < b;
    }
    bool GeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a >= b;
    }
    bool LeI64()
    {
        i64 b = TopD().IValue; PopD();
        i64 a = TopD().IValue; PopD();
        return a <= b;
    }

    bool EqF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a == b;
    }
    bool NeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a != b;
    }
    bool GtF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a > b;
    }
    bool LtF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a < b;
    }
    bool GeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a >= b;
    }
    bool LeF64()
    {
        f64 b = TopD().FValue; PopD();
        f64 a = TopD().FValue; PopD();
        return a <= b;
    }

    bool GtU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a > b;
    }
    bool LtU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a < b;
    }
    bool GeU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a >= b;
    }
    bool LeU32()
    {
        u32 b = TopW().UValue; PopW();
        u32 a = TopW().UValue; PopW();
        return a <= b;
    }

    bool GtU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a > b;
    }
    bool LtU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a < b;
    }
    bool GeU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a >= b;
    }
    bool LeU64()
    {
        u64 b = TopD().UValue; PopD();
        u64 a = TopD().UValue; PopD();
        return a <= b;
    }
} // namespace BVM::OperationStack

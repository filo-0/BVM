#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
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

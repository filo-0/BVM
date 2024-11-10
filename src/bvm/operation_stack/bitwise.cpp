#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void AndW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue &= op;
    }
    void AndD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue &= op;
    }
    void OrW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue |= op;
    }
    void OrD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue |= op;
    }
    void XorW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue ^= op;
    }
    void XorD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue ^= op;
    }
    void NotW()
    {
        TopW().UValue = ~TopW().UValue;
    }
    void NotD()
    {
        TopD().UValue = ~TopD().UValue;
    }
    void ShlW()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue <<= op;
    }
    void ShlD()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue <<= op;
    }
    void ShrI32()
    {
        i32 op = TopW().IValue;
        PopW();
        TopW().IValue >>= op;
    }
    void ShrI64()
    {
        i64 op = TopD().IValue;
        PopD();
        TopD().IValue >>= op;
    }
    void ShrU32()
    {
        u32 op = TopW().UValue;
        PopW();
        TopW().UValue >>= op;
    }
    void ShrU64()
    {
        u64 op = TopD().UValue;
        PopD();
        TopD().UValue >>= op;
    }
} // namespace BVM::OperationStack

#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
	void I32ToI8()  { OperationStack::TopW().IValue = (i8) OperationStack::TopW().IValue; }
	void I32ToI16() { OperationStack::TopW().IValue = (i16)OperationStack::TopW().IValue; }
    void I32ToI64() 
	{ 
        i32 v = OperationStack::TopW().IValue; OperationStack::PopW();
		OperationStack::PushD(v); 
	}
	void I32ToF32() { OperationStack::TopW().FValue = static_cast<f32>(OperationStack::TopW().IValue); }
	void I32ToF64() 
	{ 
		i32 v = OperationStack::TopW().IValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void I64ToI32() { OperationStack::PopW(); }
	void I64ToF32()
	{
		OperationStack::TopW(1).FValue = static_cast<f32>(OperationStack::TopD().IValue);
		OperationStack::PopW();
	}
	void I64ToF64() { OperationStack::TopD().FValue = static_cast<f64>(OperationStack::TopD().IValue); }
	void F32ToI32() { OperationStack::TopW().IValue = static_cast<i32>(OperationStack::TopW().FValue); }
	void F32ToI64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<i64>(v));
	}
	void F32ToF64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void F64ToI32()
	{
		OperationStack::TopW(1).IValue = (i32)OperationStack::TopD().FValue;
		OperationStack::PopW();
	}
	void F64ToI64() { OperationStack::TopD().IValue = static_cast<i64>(OperationStack::TopD().FValue); }
	void F64ToF32()
	{
		f64 v = OperationStack::TopD().FValue; OperationStack::PopW();
		OperationStack::TopW().FValue = static_cast<f32>(v);
	}
} // namespace BVM

#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
	void I32ToI8()  
	{ 
		i8 casted = (i8) OperationStack::TopW().IValue; 
		OperationStack::PopW();
		OperationStack::PushW((i32)casted);
	}
	void I32ToI16() 
	{ 
		i16 casted = (i16)OperationStack::TopW().IValue; 
		OperationStack::PopW();
		OperationStack::PushW((i32)casted);
	}
    void I32ToI64() 
	{ 
        i64 casted = OperationStack::TopW().IValue; 
		OperationStack::PopW();
		OperationStack::PushD(casted); 
	}
	void I32ToF32() 
	{ 
		f32 casted = (f32)OperationStack::TopW().IValue; 
		OperationStack::PopW();
		OperationStack::PushW(casted);
	}
	void I32ToF64() 
	{ 
		f64 casted = (f64)OperationStack::TopW().IValue; 
		OperationStack::PopW();
		OperationStack::PushD(casted);
	}
	void I64ToI32() { OperationStack::PopW(); }
	void I64ToF32()
	{
		f32 casted = (f32)OperationStack::TopD().IValue;
		OperationStack::PopD();
		OperationStack::PushW(casted);
	}
	void I64ToF64() 
	{ 
		f64 casted = (f64)OperationStack::TopD().IValue;
		OperationStack::PopD();
		OperationStack::PushD(casted); 
	}
	void F32ToI32() 
	{ 
		i32 casted = (i32)OperationStack::TopW().FValue;
		OperationStack::PopW();
		OperationStack::PushW(casted); 
	}
	void F32ToI64()
	{
		i64 casted = (i64)OperationStack::TopW().FValue; 
		OperationStack::PopW();
		OperationStack::PushD(casted);
	}
	void F32ToF64()
	{
		f64 casted = (f64)OperationStack::TopW().FValue; 
		OperationStack::PopW();
		OperationStack::PushD(casted);
	}
	void F64ToI32()
	{
		i32 casted = (i32)OperationStack::TopD().FValue;
		OperationStack::PopD();
		OperationStack::PushW(casted);
	}
	void F64ToI64() 
	{ 
		i64 casted = (i64)OperationStack::TopD().FValue; 
		OperationStack::PopD();
		OperationStack::PushD(casted);
	}
	void F64ToF32()
	{
		f32 casted = (f32)OperationStack::TopD().FValue; 
		OperationStack::PopW();
		OperationStack::PushW(casted);
	}
} // namespace BVM

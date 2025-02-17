#include "bvm.hpp"

namespace BVM
{
    void AddI32() { OperationStack::AddI32(); }
	void AddI64() { OperationStack::AddI64(); }
	void AddF32() { OperationStack::AddF32(); }
	void AddF64() { OperationStack::AddF64(); }
	void IncI32() 
	{
		u8 reg = GetNextByte().UValue;
		i32 op = FunctionStack::GetLocalW(reg).IValue;
		FunctionStack::SetLocalW(reg, op + 1);
	}
	void IncI64()
	{
		u8 reg = GetNextByte().UValue;
		i64 op = FunctionStack::GetLocalD(reg).IValue;
		FunctionStack::SetLocalD(reg, op + 1);
	}
	void IncF32()
	{
		u8 reg = GetNextByte().UValue;
		f32 op = FunctionStack::GetLocalW(reg).FValue;
		FunctionStack::SetLocalW(reg, op + 1);
	}
	void IncF64()
	{
		u8 reg = GetNextByte().UValue;
		f64 op = FunctionStack::GetLocalD(reg).FValue;
		FunctionStack::SetLocalD(reg, op + 1);
	}

	void SubI32() { OperationStack::SubI32(); }
	void SubI64() { OperationStack::SubI64(); }
	void SubF32() { OperationStack::SubF32(); }
	void SubF64() { OperationStack::SubF64(); }
	void DecI32()
	{
		u8 reg = GetNextByte().UValue;
		i32 op = FunctionStack::GetLocalW(reg).IValue;
		FunctionStack::SetLocalW(reg, op - 1);
	}
	void DecI64()
	{
		u8 reg = GetNextByte().UValue;
		i64 op = FunctionStack::GetLocalD(reg).IValue;
		FunctionStack::SetLocalD(reg, op - 1);
	}
	void DecF32()
	{
		u8 reg = GetNextByte().UValue;
		f32 op = FunctionStack::GetLocalW(reg).FValue;
		FunctionStack::SetLocalW(reg, op - 1);
	}
	void DecF64()
	{
		u8 reg = GetNextByte().UValue;
		f64 op = FunctionStack::GetLocalD(reg).FValue;
		FunctionStack::SetLocalD(reg, op - 1);
	}

	void MulI32() { OperationStack::MulI32(); }
	void MulI64() { OperationStack::MulI64(); }
	void MulU32() { OperationStack::MulU32(); }
	void MulU64() { OperationStack::MulU64(); }
	void MulF32() { OperationStack::MulF32(); }
	void MulF64() { OperationStack::MulF64(); }

	void DivI32() { OperationStack::DivI32(); }
	void DivI64() { OperationStack::DivI64(); }
	void DivU32() { OperationStack::DivU32(); }
	void DivU64() { OperationStack::DivU64(); }
	void DivF32() { OperationStack::DivF32(); }
	void DivF64() { OperationStack::DivF64(); }

	void ModI32() { OperationStack::ModI32(); }
	void ModU32() { OperationStack::ModI64(); }
	void ModI64() { OperationStack::ModU32(); }
	void ModU64() { OperationStack::ModU64(); }
	void ModF32() { OperationStack::ModF32(); }
	void ModF64() { OperationStack::ModF64(); }

	void NegI32() { OperationStack::NegI32(); }
	void NegI64() { OperationStack::NegI64(); }
	void NegF32() { OperationStack::NegF32(); }
	void NegF64() { OperationStack::NegF64(); }
} // namespace BVM

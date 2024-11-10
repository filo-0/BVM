#include "bvm.hpp"

namespace BVM
{
    inline static void Jump(i16 offset) { ProgramCounter += offset; }
	void Jmp()
	{
		i16 offset = GetNextHWord().IValue;
		Jump(offset);
	}

	void JmpI32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI32())
			Jump(offset);
	}
	void JmpI32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI32())
			Jump(offset);
	}
	void JmpI32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI32())
			Jump(offset);
	}
	void JmpI32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI32())
			Jump(offset);
	}
	void JmpI32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI32())
			Jump(offset);
	}
	void JmpI32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI32())
			Jump(offset);
	}

	void JmpU32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU32())
			Jump(offset);
	}
	void JmpU32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU32())
			Jump(offset);
	}
	void JmpU32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU32())
			Jump(offset);
	}
	void JmpU32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU32())
			Jump(offset);
	}

	void JmpI64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI64())
			Jump(offset);
	}
	void JmpI64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI64())
			Jump(offset);
	}
	void JmpI64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI64())
			Jump(offset);
	}
	void JmpI64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI64())
			Jump(offset);
	}
	void JmpI64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI64())
			Jump(offset);
	}
	void JmpI64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI64())
			Jump(offset);
	}

	void JmpU64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU64())
			Jump(offset);
	}
	void JmpU64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU64())
			Jump(offset);
	}
	void JmpU64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU64())
			Jump(offset);
	}
	void JmpU64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU64())
			Jump(offset);
	}

	void JmpF32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF32())
			Jump(offset);
	}
	void JmpF32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF32())
			Jump(offset);
	}
	void JmpF32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF32())
			Jump(offset);
	}
	void JmpF32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF32())
			Jump(offset);
	}
	void JmpF32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF32())
			Jump(offset);
	}
	void JmpF32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF32())
			Jump(offset);
	}

	void JmpF64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF64())
			Jump(offset);
	}
	void JmpF64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF64())
			Jump(offset);
	}
	void JmpF64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF64())
			Jump(offset);
	}
	void JmpF64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF64())
			Jump(offset);
	}
	void JmpF64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF64())
			Jump(offset);
	}
	void JmpF64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF64())
			Jump(offset);
	}
} // namespace BVM

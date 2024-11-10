#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
	void AndWord()  { OperationStack::AndW();   }
	void AndDWord() { OperationStack::AndW();   }
	void OrWord()   { OperationStack::OrW();    }
	void OrDWord()  { OperationStack::OrD();    }
	void XorWord()  { OperationStack::XorW();   }
	void XorDWord() { OperationStack::XorD();   }
	void NotWord()  { OperationStack::NotW();   }
	void NotDWord() { OperationStack::NotD();   }
	void ShlWord()  { OperationStack::ShlW();   }
	void ShlDWord() { OperationStack::ShlD();   }
	void ShrI32()   { OperationStack::ShrI32(); }
	void ShrU32()   { OperationStack::ShrU32(); }
	void ShrI64()   { OperationStack::ShrI64(); }
	void ShrU64()   { OperationStack::ShrU64(); }
} // namespace BVM

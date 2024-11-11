#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
    void DupWord()    { OperationStack::DupW();   }
	void DupWordX1()  { OperationStack::DupWX1(); }
	void DupWordX2()  { OperationStack::DupWX2(); }
	void DupDWord()   { OperationStack::DupD();   }
	void DupDWordX1() { OperationStack::DupDX1(); }
	void DupDWordX2() { OperationStack::DupDX2(); }
	void SwapWord()   { OperationStack::SwapW();  }
	void SwapDWord()  { OperationStack::SwapD();  }
} // namespace BVM

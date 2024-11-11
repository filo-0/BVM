#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
    void Alloc()
	{
		OperationStack::Alloc();
	}
	void Dealloc()
	{
		OperationStack::Dealloc();
	}
} // namespace BVM

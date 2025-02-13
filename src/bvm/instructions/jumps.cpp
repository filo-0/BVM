#include "bvm.hpp"

namespace BVM
{
    inline static void Jump(i16 offset) { ProgramCounter += offset; }
	void Jmp()
	{
		i16 offset = GetNextHWord().IValue;
		Jump(offset);
	}
	void JumpIf()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::TopW().UValue)
			Jump(offset);
		OperationStack::PopW();		
	}
} // namespace BVM

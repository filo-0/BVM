#include "bvm.hpp"

namespace BVM
{
    void PushByte0()  { OperationStack::PushW(FunctionStack::LocalB(GetNextByte().UValue, 0)); }
	void PushByte1()  { OperationStack::PushW(FunctionStack::LocalB(GetNextByte().UValue, 1)); }
	void PushByte2()  { OperationStack::PushW(FunctionStack::LocalB(GetNextByte().UValue, 2)); }
	void PushByte3()  { OperationStack::PushW(FunctionStack::LocalB(GetNextByte().UValue, 3)); }
	void PushHWord0() { OperationStack::PushW(FunctionStack::LocalH(GetNextByte().UValue, 0)); }
	void PushHWord2() { OperationStack::PushW(FunctionStack::LocalH(GetNextByte().UValue, 1)); }
	void PushWord()   { OperationStack::PushW(FunctionStack::LocalW(GetNextByte().UValue));  }
	void PushWord0()  { OperationStack::PushW(FunctionStack::LocalW(0));                     }
	void PushWord1()  { OperationStack::PushW(FunctionStack::LocalW(1));                     }
	void PushWord2()  { OperationStack::PushW(FunctionStack::LocalW(2));                     }
	void PushWord3()  { OperationStack::PushW(FunctionStack::LocalW(3));                     }
	void PushDWord()  { OperationStack::PushD(FunctionStack::LocalD(GetNextByte().UValue));  }
	void PushDWord0() { OperationStack::PushD(FunctionStack::LocalD(0));                     }
	void PushDWord1() { OperationStack::PushD(FunctionStack::LocalD(1));                     }
	void PushDWord2() { OperationStack::PushD(FunctionStack::LocalD(2));                     }
	void PushDWord3() { OperationStack::PushD(FunctionStack::LocalD(3));                     }
	void PushWords()
	{
		HWord params = GetNextHWord();
		OperationStack::PushWs(&FunctionStack::LocalW(params.BValue[0].UValue), params.BValue[1].UValue);
	}
    void GetAddress()  { OperationStack::PushD(reinterpret_cast<u64>(&FunctionStack::LocalW(Bytecode[ProgramCounter++]))); }

	void PushWordValue0()  { OperationStack::PushW(0); }
	void PushDWordValue0() { OperationStack::PushD(0); }
	void PushI32_1() { OperationStack::PushW(1);    }
	void PushI32_2() { OperationStack::PushW(2);    }
	void PushI64_1() { OperationStack::PushD(1);    }
	void PushI64_2() { OperationStack::PushD(2);    }
	void PushF32_1() { OperationStack::PushW(1.0f); }
	void PushF32_2() { OperationStack::PushW(2.0f); }
	void PushF64_1() { OperationStack::PushD(1.0);  }
	void PushF64_2() { OperationStack::PushD(2.0);  }
	void PushI8AsI32() { OperationStack::PushW(GetNextByte().IValue); }
	void PushI8AsI64() { OperationStack::PushD(GetNextByte().IValue); }
	void PushWordFromPool()      { OperationStack::PushW(WordConstantPool[GetNextByte().UValue]);   }
	void PushWordFromPoolWide()  { OperationStack::PushW(WordConstantPool[GetNextHWord().UValue]);  }
	void PushDWordFromPool()     { OperationStack::PushD(DWordConstantPool[GetNextByte().UValue]);  }
	void PushDWordFromPoolWide() { OperationStack::PushD(DWordConstantPool[GetNextHWord().UValue]); }
	void PushStringFromPool()    { OperationStack::PushD(StringConstantPool[GetNextByte().UValue]);  }
	void PushStringFromPoolWide(){ OperationStack::PushD(StringConstantPool[GetNextHWord().UValue]); }
} // namespace BVM

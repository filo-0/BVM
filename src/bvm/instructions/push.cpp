#include "bvm.hpp"

namespace BVM
{
	void PushWord()   { OperationStack::PushW(FunctionStack::GetLocalW(GetNextByte().UValue));  }
	void PushWord0()  { OperationStack::PushW(FunctionStack::GetLocalW(0));                     }
	void PushWord1()  { OperationStack::PushW(FunctionStack::GetLocalW(1));                     }
	void PushWord2()  { OperationStack::PushW(FunctionStack::GetLocalW(2));                     }
	void PushWord3()  { OperationStack::PushW(FunctionStack::GetLocalW(3));                     }
	void PushDWord()  { OperationStack::PushD(FunctionStack::GetLocalD(GetNextByte().UValue));  }
	void PushDWord0() { OperationStack::PushD(FunctionStack::GetLocalD(0));                     }
	void PushDWord1() { OperationStack::PushD(FunctionStack::GetLocalD(1));                     }
	void PushDWord2() { OperationStack::PushD(FunctionStack::GetLocalD(2));                     }
	void PushDWord3() { OperationStack::PushD(FunctionStack::GetLocalD(3));                     }
	void PushWords()
	{
		u8 loc = GetNextByte().UValue;
		u8 count = GetNextByte().UValue;
		OperationStack::PushWs(FunctionStack::GetLocalRef(loc), count);			
	}

    void GetAddress()  { OperationStack::PushD(FunctionStack::GetLocalRef(GetNextByte().UValue)); }

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

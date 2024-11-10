#include "bvm.hpp"

namespace BVM
{
    void LoadByte0()   { OperationStack::LoadB(0);  }
	void LoadByte1()   { OperationStack::LoadB(1);  }
	void LoadByte2()   { OperationStack::LoadB(2);  }
	void LoadByte3()   { OperationStack::LoadB(3);  }
	void LoadHWord0()  { OperationStack::LoadH(0);  }
	void LoadHWord2()  { OperationStack::LoadH(1);  }
	void LoadWord()    { OperationStack::LoadW();   }
	void LoadDWord()   { OperationStack::LoadD();   }
	void LoadWords()   { OperationStack::LoadWs(GetNextByte().UValue); }
	void LoadBufferByteVal() { OperationStack::LoadBufferByteVal(); }
	void LoadBufferHWordVal(){ OperationStack::LoadBufferHWordVal(); }
	void LoadBufferWordVal() { OperationStack::LoadBufferWordVal(); }
	void LoadBufferDWordVal(){ OperationStack::LoadBufferDwordVal(); }
	void LoadBufferWordsVal(){ OperationStack::LoadBufferWordsVal(GetNextByte().UValue); }
	void LoadBufferByteRef() { OperationStack::LoadBufferByteRef(); }
	void LoadBufferHWordRef(){ OperationStack::LoadBufferHWordRef(); }
	void LoadBufferWordRef() { OperationStack::LoadBufferWordRef(); }
	void LoadBufferDWordRef(){ OperationStack::LoadBufferDWordRef(); }
	void LoadBufferWordsRef(){ OperationStack::LoadBufferWordsRef(GetNextByte().UValue); }

	void LoadOffsetByte0() { OperationStack::LoadOffsetByte(GetNextByte().UValue, 0); }
	void LoadOffsetByte1() { OperationStack::LoadOffsetByte(GetNextByte().UValue, 1); }
	void LoadOffsetByte2() { OperationStack::LoadOffsetByte(GetNextByte().UValue, 2); }
	void LoadOffsetByte3() { OperationStack::LoadOffsetByte(GetNextByte().UValue, 3); }
	void LoadOffsetHWord0() { OperationStack::LoadOffsetHWord(GetNextByte().UValue, 0); }
	void LoadOffsetHWord2() { OperationStack::LoadOffsetHWord(GetNextByte().UValue, 1); }
	void LoadOffsetWord()   { OperationStack::LoadOffsetWord(GetNextByte().UValue);   }
	void LoadOffsetDWord()  { OperationStack::LoadOffsetDWord(GetNextByte().UValue);  }
	void LoadOffsetWords()  
	{ 
		u8 offset = GetNextByte().UValue;
		u8 n = GetNextByte().UValue;
		OperationStack::LoadOffsetWords(offset, n); 
	}
} // namespace BVM

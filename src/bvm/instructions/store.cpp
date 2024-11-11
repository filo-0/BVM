#include "bvm.hpp"

namespace BVM
{
    void StoreByte0()  { OperationStack::StoreB(0); }
	void StoreByte1()  { OperationStack::StoreB(1); }
	void StoreByte2()  { OperationStack::StoreB(2); }
	void StoreByte3()  { OperationStack::StoreB(3); }
	void StoreHWord0() { OperationStack::StoreH(0); }
	void StoreHWord2() { OperationStack::StoreH(1); }
	void StoreWord()   { OperationStack::StoreW();  }
	void StoreDWord()  { OperationStack::StoreD();  }
	void StoreWords()  { OperationStack::StoreWs(GetNextByte().UValue); }	

	void StoreBufferByte() { OperationStack::StoreBufferByte();  }
	void StoreBufferHWord(){ OperationStack::StoreBufferHWord(); }
	void StoreBufferWord() { OperationStack::StoreBufferWord();  }
	void StoreBufferDWord(){ OperationStack::StoreBufferDWord(); }
	void StoreBufferWords(){ OperationStack::StoreBufferWords(GetNextByte().UValue); }

	void StoreOffsetByte0()  { OperationStack::StoreOffsetByte(GetNextByte().UValue, 0);  }
	void StoreOffsetByte1()  { OperationStack::StoreOffsetByte(GetNextByte().UValue, 1);  }
	void StoreOffsetByte2()  { OperationStack::StoreOffsetByte(GetNextByte().UValue, 2);  }
	void StoreOffsetByte3()  { OperationStack::StoreOffsetByte(GetNextByte().UValue, 3);  }
	void StoreOffsetHWord0() { OperationStack::StoreOffsetHWord(GetNextByte().UValue, 0); }
	void StoreOffsetHWord2() { OperationStack::StoreOffsetHWord(GetNextByte().UValue, 1); }
	void StoreOffsetWord()   { OperationStack::StoreOffsetWord(GetNextByte().UValue);     }
	void StoreOffsetDWord()  { OperationStack::StoreOffsetDWord(GetNextByte().UValue);    }
	void StoreOffsetWords()  
	{ 
		u8 offset = GetNextByte().UValue;
		u8 n = GetNextByte().UValue;
		OperationStack::StoreOffsetWords(offset, n); 
	}
} // namespace BVM

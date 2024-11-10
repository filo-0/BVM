#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void Alloc()
    {
        u32 count = TopW().UValue; PopW();
        void* buffer = new Byte[count];
        PushD(buffer);
    }
    void Dealloc()
    {
        Byte* buffer = TopD().BPointer;
        delete[] buffer;
        PopD();
    }
} // namespace BVM::OpreationStack

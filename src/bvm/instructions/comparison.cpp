#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"
namespace BVM
{
    void CmpEqWord() { OperationStack::CmpEqW(); }
    void CmpEqDWord() { OperationStack::CmpEqD(); }
    void CmpLtI32() { OperationStack::CmpLtI32(); }
    void CmpLeI32() { OperationStack::CmpLeI32(); }
    void CmpLtI64() { OperationStack::CmpLtI64(); }
    void CmpLeI64() { OperationStack::CmpLeI64(); }
    void CmpLtU32() { OperationStack::CmpLtU32(); }
    void CmpLeU32() { OperationStack::CmpLeU32(); }
    void CmpLtU64() { OperationStack::CmpLtU64(); }
    void CmpLeU64() { OperationStack::CmpLeU64(); }
    void CmpLtF32() { OperationStack::CmpLtF32(); }
    void CmpLeF32() { OperationStack::CmpLeF32(); }
    void CmpLtF64() { OperationStack::CmpLtF64(); }
    void CmpLeF64() { OperationStack::CmpLeF64(); }
}
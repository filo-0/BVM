#include "bvm/instructions.hpp"
#include "bvm/operation_stack.hpp"

namespace BVM
{
    void CmpEqWord() { OperationStack::CmpEqW(); }
    void CmpEqDWord() { OperationStack::CmpEqD(); }
    void CmpNeWord() { OperationStack::CmpNeW(); }
    void CmpNeDWord() { OperationStack::CmpNeD(); }

    void CmpLtI32() { OperationStack::CmpLtI32(); }
    void CmpGtI32() { OperationStack::CmpGtI32(); }
    void CmpLeI32() { OperationStack::CmpLeI32(); }
    void CmpGeI32() { OperationStack::CmpLtI64(); }

    void CmpLtI64() { OperationStack::CmpLtI64(); }
    void CmpGtI64() { OperationStack::CmpGtI64(); }
    void CmpLeI64() { OperationStack::CmpLeI64(); }
    void CmpGeI64() { OperationStack::CmpGeI64(); }

    void CmpLtU32() { OperationStack::CmpLtU32(); }
    void CmpGtU32() { OperationStack::CmpGtU32(); }
    void CmpLeU32() { OperationStack::CmpLeU32(); }
    void CmpGeU32() { OperationStack::CmpGeU32(); }

    void CmpLtU64() { OperationStack::CmpLtU64(); }
    void CmpGtU64() { OperationStack::CmpGtU64(); }
    void CmpLeU64() { OperationStack::CmpLeU64(); }
    void CmpGeU64() { OperationStack::CmpGeU64(); }

    void CmpLtF32() { OperationStack::CmpLtF32(); }
    void CmpGtF32() { OperationStack::CmpGtF32(); }
    void CmpLeF32() { OperationStack::CmpLeF32(); }
    void CmpGeF32() { OperationStack::CmpGeF32(); }

    void CmpLtF64() { OperationStack::CmpLtF64(); }
    void CmpGtF64() { OperationStack::CmpGtF64(); }
    void CmpLeF64() { OperationStack::CmpLeF64(); }
    void CmpGeF64() { OperationStack::CmpGeF64(); }
}
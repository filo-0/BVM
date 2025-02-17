#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void DupW() { PushW(TopW()); }
    void DupWX1()
    {
        SwpW(0, 1);
        PushW(TopW(1));
    }
    void DupWX2()
    {
        SwpW(1, 2);
        SwpW(0, 2);
        PushW(TopW(2));
    }
    void DupD() { PushD(TopD()); }
    void DupDX1()
    {
        SwpW(0, 2);
        SwpW(1, 2);
        PushD(TopD(1));
    }
    void DupDX2()
    {
        SwpD(0, 2);
        PushD(TopD(2));
    }
    void SwapW()   { SwpW(0, 1); }
    void SwapWX1() { SwpW(1, 2); }
    void SwapWX2() { SwpW(2, 3); }
    void SwapD()   { SwpD(0, 2); }
    void SwapDX1() { SwpD(1, 3); }
    void SwapDX2() { SwpD(2, 4); }

} // namespace BVM::OperationStack

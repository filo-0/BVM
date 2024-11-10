#include <algorithm>

#include "bvm/operation_stack.hpp"

namespace BVM::OperationStack
{
    void DupW() { PushW(TopW()); }
    void DupWX1()
    {
        std::swap(TopW(0), TopW(1));
        PushW(TopW(1));
    }
    void DupWX2()
    {
        std::swap(TopW(1), TopW(2));
        std::swap(TopW(0), TopW(2));
        PushW(TopW(2));
    }
    void DupD() { PushD(TopD()); }
    void DupDX1()
    {
        std::swap(TopW(0), TopW(2));
        std::swap(TopW(1), TopW(2));
        PushD(TopD(1));
    }
    void DupDX2()
    {
        std::swap(TopD(0), TopD(2));
        PushD(TopD(2));
    }
    void SwapW()   { std::swap(TopW(0), TopW(1)); }
    void SwapWX1() { std::swap(TopW(1), TopW(2)); }
    void SwapWX2() { std::swap(TopW(2), TopW(3)); }
    void SwapD()   { std::swap(TopD(0), TopD(2)); }
    void SwapDX1() { std::swap(TopD(1), TopD(3)); }
    void SwapDX2() { std::swap(TopD(2), TopD(4)); }

} // namespace BVM::OperationStack

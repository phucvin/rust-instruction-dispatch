// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <array>
#include <cstdio>

#if DIRECT_THREADING
#    error "direct threading is not supported"
#endif

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc);

[[gnu::noinline]] int do_print_impl(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr,
                                    const bytecode& bc)
{
    std::puts("42");
    ++ip;
    [[clang::musttail]] return dispatch(ip, vstack_ptr, cstack_ptr, bc);
}

#define BYTECODE_OP(Name, ...)                                                                     \
    int do_execute_##Name(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr,                \
                          const bytecode& bc)                                                      \
    {                                                                                              \
        __VA_ARGS__                                                                                \
        [[clang::musttail]] return dispatch(ip, vstack_ptr, cstack_ptr, bc);                       \
    }
#include "bytecode_ops.inl"
#undef BYTECODE_OP

[[gnu::always_inline]] int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr,
                                    const bytecode& bc)
{
    switch (ip->op)
    {
#define BYTECODE_OP(Name, ...)                                                                     \
    case bytecode_op::Name:                                                                        \
        [[clang::musttail]] return do_execute_##Name(ip, vstack_ptr, cstack_ptr, bc);
#include "bytecode_ops.inl"
#undef BYTECODE_OP

    default:
        __builtin_unreachable();
    }
}
// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <array>
#include <cstdio>

#if !DIRECT_THREADING
#    error "direct threading is required"
#endif

[[gnu::noinline]] int do_print_impl(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr,
                                    const bytecode& bc)
{
    std::puts("42");
    ++ip;
    [[clang::musttail]] return ip->op(ip, vstack_ptr, cstack_ptr, bc);
}

#define BYTECODE_OP(Name, ...)                                                                     \
    int bytecode_op::Name(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr,                \
                          const bytecode& bc)                                                      \
    {                                                                                              \
        __VA_ARGS__                                                                                \
        [[clang::musttail]] return ip->op(ip, vstack_ptr, cstack_ptr, bc);                         \
    }
#include "bytecode_ops.inl"
#undef BYTECODE_OP

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc)
{
    [[clang::musttail]] return ip->op(ip, vstack_ptr, cstack_ptr, bc);
}
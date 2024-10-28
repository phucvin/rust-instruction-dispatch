// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <array>
#include <cstdio>

#if DIRECT_THREADING
#    error "direct threading is not supported"
#endif

#define BYTECODE_OP(Name, ...)                                                                     \
    int do_execute_##Name(bytecode_ip& ip, int*& vstack_ptr, bytecode_ip*& cstack_ptr,             \
                          const bytecode& bc)                                                      \
    {                                                                                              \
        __VA_ARGS__                                                                                \
        return 0;                                                                                  \
    }
#include "bytecode_ops.inl"
#undef BYTECODE_OP

constexpr std::array<int (*)(bytecode_ip&, int*&, bytecode_ip*&, const bytecode&), 12> execute_table = {
#define BYTECODE_OP(Name, ...) &do_execute_##Name,
#include "bytecode_ops.inl"
#undef BYTECODE_OP
};

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc)
{
    while (ip->op != bytecode_op::exit)
    {
        execute_table[int(ip->op)](ip, vstack_ptr, cstack_ptr, bc);
    }

    return *--vstack_ptr;
}
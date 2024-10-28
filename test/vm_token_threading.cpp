// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <array>
#include <cstdio>

#if DIRECT_THREADING
#    error "direct threading is not supported"
#endif

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc)
{
    constexpr std::array<void*, 12> execute_table = {
#define BYTECODE_OP(Name, ...) &&do_execute_##Name,
#include "bytecode_ops.inl"
#undef BYTECODE_OP
    };
    goto* execute_table[int(ip->op)];

#define BYTECODE_OP(Name, ...) do_execute_##Name : __VA_ARGS__ goto* execute_table[int(ip->op)];
#include "bytecode_ops.inl"
#undef BYTECODE_OP
}
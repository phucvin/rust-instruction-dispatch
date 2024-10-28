// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <cstdio>

#if DIRECT_THREADING
#    error "inline threading is not supported"
#endif

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc)
{
    while (true)
    {
        switch (ip->op)
        {
#define BYTECODE_OP(Name, ...)                                                                     \
    case bytecode_op::Name:                                                                        \
        __VA_ARGS__ break;
#include "bytecode_ops.inl"
#undef BYTECODE_OP

        default:
            __builtin_unreachable();
        }
    }
}
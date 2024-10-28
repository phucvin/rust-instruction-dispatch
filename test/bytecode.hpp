// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#ifndef BYTECODE_HPP_INCLUDED
#define BYTECODE_HPP_INCLUDED

#include <cstdint>
#include <vector>

union bytecode_inst;
using bytecode    = std::vector<bytecode_inst>;
using bytecode_ip = const bytecode_inst*;

#if DIRECT_THREADING

#    define DECLARE_OP(Op)                                                                         \
        int Op(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc);

using bytecode_op_t = int (*)(bytecode_ip, int*, bytecode_ip*, const bytecode&);

namespace bytecode_op
{
#    define BYTECODE_OP(Name, ...) int Name(bytecode_ip, int*, bytecode_ip*, const bytecode&);
#    include "bytecode_ops.inl"
#    undef BYTECODE_OP
} // namespace bytecode_op

#else

enum class bytecode_op : std::uint8_t
{
#    define BYTECODE_OP(Name, ...) Name,
#    include "bytecode_ops.inl"
#    undef BYTECODE_OP
};

using bytecode_op_t = bytecode_op;

#endif

union bytecode_inst
{
    bytecode_op_t op;
    std::uint8_t  value;
    std::int8_t   offset;

    bytecode_inst(bytecode_op_t op) : op(op) {}
    bytecode_inst(std::uint8_t value) : value(value) {}
    bytecode_inst(std::int8_t offset) : offset(offset) {}
    template <typename T>
    bytecode_inst(T) = delete;
};

#endif // BYTECODE_HPP_INCLUDED
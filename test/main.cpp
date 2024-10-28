// Copyright (C) 2022 Jonathan Müller
// SPDX-License-Identifier: BSL-1.0

#include "bytecode.hpp"
#include <cstdio>

int dispatch(bytecode_ip ip, int* vstack_ptr, bytecode_ip* cstack_ptr, const bytecode& bc);

int execute(const bytecode& bc, int argument)
{
    constexpr auto vstack_size = 256;
    constexpr auto cstack_size = 256;

    int         vstack[vstack_size];
    bytecode_ip cstack[cstack_size];

    auto ip         = bc.data();
    auto vstack_ptr = &vstack[0];
    auto cstack_ptr = &cstack[0];

    static const bytecode_inst exit(bytecode_op::exit);
    *cstack_ptr++ = &exit;
    *vstack_ptr++ = argument;

    return dispatch(ip, vstack_ptr, cstack_ptr, bc);
}

bytecode fib(bool print42)
{
    bytecode result;

    if (print42)
        result.push_back(bytecode_op::print42);

    // if (n < 2)
    result.push_back(bytecode_op::dup);
    result.push_back(bytecode_op::push);
    result.push_back(std::uint8_t(2));
    result.push_back(bytecode_op::cmp_ge);
    result.push_back(bytecode_op::jump_if);
    result.push_back(std::int8_t(2 + 1));

    // return n
    result.push_back(bytecode_op::return_);

    // return fib(n - 1) + fib(n - 2)
    result.push_back(bytecode_op::dup);
    result.push_back(bytecode_op::push);
    result.push_back(std::uint8_t(1));
    result.push_back(bytecode_op::sub);
    result.push_back(bytecode_op::recurse);

    result.push_back(bytecode_op::swap);
    result.push_back(bytecode_op::push);
    result.push_back(std::uint8_t(2));
    result.push_back(bytecode_op::sub);
    result.push_back(bytecode_op::recurse);

    result.push_back(bytecode_op::add);
    result.push_back(bytecode_op::return_);

    return result;
}

int main()
{
    auto result = execute(fib(false), 35);
    if (result != 9227465)
        return 1;

    std::printf("result: %d\n", result);
}
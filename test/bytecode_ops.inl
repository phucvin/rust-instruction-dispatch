BYTECODE_OP(push, //
            {
                *vstack_ptr++ = ip[1].value;
                ip += 2;
            })

BYTECODE_OP(dup, //
            {
                auto top      = vstack_ptr[-1];
                *vstack_ptr++ = top;
                ++ip;
            })
BYTECODE_OP(swap, //
            {
                auto rhs      = *--vstack_ptr;
                auto lhs      = *--vstack_ptr;
                *vstack_ptr++ = rhs;
                *vstack_ptr++ = lhs;
                ++ip;
            })

BYTECODE_OP(add, //
            {
                auto rhs      = *--vstack_ptr;
                auto lhs      = *--vstack_ptr;
                *vstack_ptr++ = lhs + rhs;
                ++ip;
            })
BYTECODE_OP(sub, //
            {
                auto rhs      = *--vstack_ptr;
                auto lhs      = *--vstack_ptr;
                *vstack_ptr++ = lhs - rhs;
                ++ip;
            })
BYTECODE_OP(cmp_ge, //
            {
                auto rhs      = *--vstack_ptr;
                auto lhs      = *--vstack_ptr;
                *vstack_ptr++ = lhs >= rhs;
                ++ip;
            })

BYTECODE_OP(jump_if, //
            {
                auto condition = *--vstack_ptr;
                if (condition != 0)
                    ip += ip[1].offset;
                else
                    ip += 2;
            })
BYTECODE_OP(recurse, //
            {
                *cstack_ptr++ = ip + 1;
                ip            = bc.data();
            })
BYTECODE_OP(return_, //
            { ip = *--cstack_ptr; })

#if HOIST_PRINT42
BYTECODE_OP(print42, //
            {
                if (vstack_ptr[0] == 42) [[clang::musttail]]
                    return do_print_impl(ip, vstack_ptr, cstack_ptr, bc);
                ++ip;
            })
#else
BYTECODE_OP(print42, //
            {
                if (vstack_ptr[0] == 42)
                    std::puts("42");
                ++ip;
            })
#endif

BYTECODE_OP(exit, //
            { return *--vstack_ptr; })
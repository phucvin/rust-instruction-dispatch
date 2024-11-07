cd ..

curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

. "$HOME/.cargo/env"

cd C/switch-dispatch

make

./switch-dispatch

C/switch-dispatch | Average of 100 results:    4849323 ns

C/direct-call-theading | Average of 100 results:    7786002 ns

C/optimized_direct_threading | Average of 100 results:    5081872 ns

C/direct-tail-call-threading | Average of 100 results:    2502826 ns

Rust/switch-dispatch | Average of 100 results:    5209324 ns

Rust/direct-call-theading | Average of 100 results:    7507662 ns

Rust/optimized_direct_threading | Average of 100 results:    16245343 ns

Rust/direct-tail-call-threading | Average of 100 results:    3176299 ns

cd test

clang++ -Os vm_switch.cpp main.cpp -o vm_switch.out && time ./vm_switch.out

> 0.314s

clang++ -Os vm_call_threading.cpp main.cpp -o vm_call_threading.out && time ./vm_call_threading.out

> 0.819s

clang++ -Os vm_token_threading.cpp main.cpp -o vm_token_threading.out && time ./vm_token_threading.out

> 0.372s

clang++ -DDIRECT_THREADING -Os vm_direct_tail_call.cpp main.cpp -o vm_direct_tail_call.out && time ./vm_direct_tail_call.out

> 0.262s

clang++ -Os vm_switch_tail_call.cpp main.cpp -o vm_switch_tail_call.out && time ./vm_switch_tail_call.out

> 0.411s

clang++ -Os vm_token_tail_call.cpp main.cpp -o vm_token_tail_call.out && time ./vm_token_tail_call.out

> 0.375s

See also:
- https://github.com/vshymanskyy/interp
- https://gist.github.com/foonathan/f034c74feb6f78e867e596a362ecdb3c
- https://github.com/pliniker/dispatchers

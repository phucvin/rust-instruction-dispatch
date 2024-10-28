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

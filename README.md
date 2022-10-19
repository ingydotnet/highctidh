This is an unofficial fork of high-ctidh. This is highly experimental software
and has not yet been reviewed for security considerations.

This fork enhances high-ctidh with additional Makefile targets including
building high-ctidh as four shared libraries, one for each key size of 511,
512, 1024, and 2048. Python bindings are additionally added, as well as
optional Debian packaging of both the shared library object files and the
Python module.  The Python bindings were made in concert with the author of the
highctidh `ctidh_cgo` Golang bindings available at
https://git.xx.network/elixxir/ctidh_cgo/. Both bindings were built around the
same shared objects for cross verification purposes. Currently this library is
fast on the `x86_64` CPU architecture and functional but much slower with other
CPU architectures. The portable backend was generated using the `fiat-crypto`
project which uses a "Correct-by-Construction" approach; see `PRIMES.md` for
more information. Tested architectures include: `arm32/armv7l`,
`arm64/aarch64`, `loongarch64/Loongson`, `mips64/mips64el`, `POWER8/ppc64`,
`POWER9/ppc64le`, `riscv64`, `s390x`, `sparc64`, and `x86_64`. To see rough
performance numbers, look at `BENCHMARKS.md`. We recommend using gcc 10 or
later as the compiler except on `mips64/mips64el` and `arm32/armv7l` where we
recommend clang 14.

To build we recommend:

   sudo apt install gcc clang make build-essential python3-pytest

To build and install the shared library files using the
"Correct-by-Construction" fiat-crypto portable C backend:

    make libhighctidh.so HIGHCTIDH_PORTABLE=1
    sudo make install

To build and install the shared library files using the `x86_64` assembler
backend:

    make libhighctidh.so HIGHCTIDH_PORTABLE=0
    sudo make install

By default `HIGHCTIDH_PORTABLE=1` is enabled for all platforms.

To test without installing run the `test` target:

   make test

An example C program that can use any of the
libhighctidh_{511,512,1024,2048}.so libraries is available in
`example-ctidh.c`. Use the `make examples` target to build `example-ctidh511`,
`example-ctidh512`, `example-ctidh1024`, and `example-ctidh2048` programs.

A basic Python benchmarking program `highctidh-simple-benchmark.py` shows
general performance numbers.

More information about the Python bindings including installation instructions
are available in the `README.python.md` file.

The original authors of this software released high-ctidh in the public domain.
All contributions made in this fork are also in the public domain.

The original released README is `README.original.md`.

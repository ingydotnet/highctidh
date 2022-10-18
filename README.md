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

To build and install the shared library files using the
"Correct-by-Construction" fiat-crypto portable C backend:

    ./autogen
    make libhighctidh.so HIGHCTIDH_PORTABLE=1
    sudo make install

To build and install the shared library files using the `x86_64` assembler
backend:

    ./autogen
    make libhighctidh.so HIGHCTIDH_PORTABLE=0
    sudo make install

By default `HIGHCTIDH_PORTABLE=1` is enabled for all platforms.

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

Prerequisites: Intel or AMD CPU with `adcx`/`adox`: i.e., Broadwell,
Skylake, or newer. Linux with standard development tools plus `clang`
plus `valgrind`.

To download and unpack the latest version:

        wget -m https://ctidh.isogeny.org/high-ctidh-latest-version.txt
        version=$(cat ctidh.isogeny.org/high-ctidh-latest-version.txt)
        wget -m https://ctidh.isogeny.org/high-ctidh-$version.tar.gz
        tar -xzf ctidh.isogeny.org/high-ctidh-$version.tar.gz
        cd high-ctidh-$version

To compile, test for functionality, tune for multiplications, and tune
for cycles, for all selected sizes (511, 512, 1024, 2048):

        make

This takes a while because of all the testing and tuning. Any test
failure will stop the build process. You can separately run

        make generic # size-independent tests, 8.6 minutes
        make 511 # size 511, 1.5 minutes
        make 512 # size 512, 1.7 minutes
        make 1024 # size 1024, 25 minutes
        make 2048 # size 2048, 549 minutes

where the timings shown here are on a 3GHz Skylake core.

(Tuning for multiplications is machine-independent and can be
precomputed. Tuning for cycles can be precomputed per microarchitecture.
One can carry out both precomputations more efficiently by starting with
measurements of `tree1`, `multiprod2`, `multiprod2_selfreciprocal`,
`multieval_precompute`, and `multieval_postcompute`; the Python scripts
include a preliminary implementation of this for the multiplication
tuning, currently used only as a double-check.)

The functionality testing included in "`make`" does not include a
constant-time test. To run a constant-time test for all selected sizes:

        make timecop # 25 minutes

For benchmarks regarding, e.g., size-511 code tuned for multiplications:

        ./bench511mults 16383 > bench511mults.out.16383

This runs a million experiments: more precisely, 16383 experiments for
each of 65 keys. This takes hours, and generates hundreds of megabytes
of data. Each measurement includes, for validation and separately for
the action, a "`mulsq`" count that includes both multiplications and
squarings, a "`sq`" count that includes only squarings, an "`addsub`"
count that includes additions and subtractions, and a cycle count (which
for multiplication-tuned code isn't far behind cycle-tuned code). The
action also shows "`stattried`" counts showing the number of times each
batch occurred publicly in an atomic block.

To analyze average costs and standard deviations:

        ./analyze-costs < bench511mults.out.16383 \
        > bench511mults.out.16383.analyze-costs

Statistics are printed for each of the 65 keys separately, and
("`total`") for the all of the experiments together.

To analyze whether the "`stattried`" counts are as expected:

        ./analyze-pr < bench511mults.out.16383 \
        > bench511mults.out.16383.analyze-pr

This prints, for each batch, 1−1/p times the number of times the batch
was tried divided by the batch bound, where p is the smallest prime in
the batch.

For various size-511 microbenchmarks:

        ./umults511
        ./ubench511

To select other CSIDH sizes and other CTIDH parameters (subject to
various undocumented restrictions), edit the table at the top of
`autogen` and run "`./autogen; make`".

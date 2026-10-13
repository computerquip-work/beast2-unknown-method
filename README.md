# Beast2 unknown method reproduction

Beast2 passes `method::unknown` to the router, which rejects it by throwing.

Requires CMake 3.25+ and a C/C++ toolchain with C++20 support. CMake downloads pinned Boost,
Capy, HTTP and Beast2 sources into the build directory. No installed Boost,
Conan, OpenSSL or Corosio is needed; no third-party code is committed here.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target repro -j4
./build/repro
```

The 23-line program feeds `CUSTOM /records` directly into Beast2's session loop
using Capy's test streams. No network or custom stream implementation is needed.

Expected: HTTP 501, exit 0. Observed on GCC 16.2.1/Linux: uncaught
`std::invalid_argument: invalid argument`, SIGABRT.
The program returns 0 only when it receives the expected rejection response.

To test a local Beast2 checkout, add
`-DFETCHCONTENT_SOURCE_DIR_BEAST2=/absolute/path/to/beast2` when configuring.
The same override works for `BOOST`, `CAPY` and `HTTP`, including offline builds
when all four source trees are provided. Use a fresh build directory when
switching dependency revisions.

Only Beast2's original `src/http_worker.cpp` is compiled, linked with the
upstream HTTP and Capy targets. This exercises the session loop without
building socket listeners or TLS backends.

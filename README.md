# Beast2 unknown method reproduction

Beast2 passes `method::unknown` to the router, which rejects it by throwing.

Requires CMake 3.25+, a C++20 compiler and OpenSSL development files.
FetchContent downloads pinned, unpatched upstream sources; no Conan is used.

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

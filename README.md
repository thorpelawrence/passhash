# Build
Build with cmake

## Linux
Dependencies:
```
OpenSSL, GTK3, libsodium
```

To compile:
```
mkdir build
cd build
cmake ..
make
```

To build with debug symbols: `cmake .. -DCMAKE_BUILD_TYPE=Debug`

## Windows (no-gui)
Dependencies:
```
OpenSSL, libsodium
```

To compile:
```
mkdir build
cd build
cmake -Dsodium_DIR="path\\to\\libsodium" ..
Open solution in Visual Studio and build
```


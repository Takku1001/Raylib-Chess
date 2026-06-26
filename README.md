# Raylib-Chess

A two-player chess game in C++ using [raylib](https://www.raylib.com/), built with object-oriented design (each piece is a class derived from an abstract `Piece` base, driven by a `Board` engine). Made as an OOP course project.

## Features

- Full move validation for every piece
- Check, checkmate, and stalemate detection
- Pawn promotion (Queen / Rook / Bishop / Knight)
- Legal-move highlighting and self-check prevention

## Tech Stack

- C++17, raylib 5.5
- CMake build, dependencies via [vcpkg](https://vcpkg.io/)
- Tested on Windows x64 (MSVC)

## Structure

```
src/            # source (.cpp) — board engine, piece logic, rendering
include/        # headers (.h)
assets/         # board and piece sprites (PNG)
CMakeLists.txt  # build configuration
```

## Build & Run

1. Install raylib via vcpkg:
   ```powershell
   vcpkg install raylib:x64-windows
   ```
2. Configure and build, pointing CMake at the vcpkg toolchain:
   ```powershell
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Debug
   ```
3. Run the executable (assets are copied next to it automatically):
   ```powershell
   ./build/Debug/chess.exe
   ```

## Controls

- **Left-click** — select a piece, then click the target square to move
- **Right-click** — deselect
- **1–4** — choose piece on pawn promotion
- **Esc** — quit

## Author

**Muhammad Rayyan Malik**

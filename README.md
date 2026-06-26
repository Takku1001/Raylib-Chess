# Raylib-Chess

A two-player chess game in C++ using [raylib](https://www.raylib.com/), built with object-oriented design (each piece is a class derived from an abstract `Piece` base, driven by a `Board` engine). Made as an OOP course project.

## Features

- Full move validation for every piece
- Check, checkmate, and stalemate detection
- Pawn promotion (Queen / Rook / Bishop / Knight)
- Legal-move highlighting and self-check prevention

## Tech Stack

- C++17, raylib 5.5
- Visual Studio 2022 (MSVC v143), dependencies via [vcpkg](https://vcpkg.io/)
- Windows x64

## Structure

```
src/        # source (.cpp) — board engine, piece logic, rendering
include/    # headers (.h)
assets/     # board and piece sprites (PNG)
CHESS-3.sln # Visual Studio solution
```

## Build & Run

1. Install raylib via vcpkg:
   ```powershell
   vcpkg install raylib:x64-windows
   vcpkg integrate install
   ```
2. Open `CHESS-3.sln` in Visual Studio 2022, set platform to **x64**, and press **F5**.

## Controls

- **Left-click** — select a piece, then click the target square to move
- **Right-click** — deselect
- **1–4** — choose piece on pawn promotion
- **Esc** — quit

## Author

**Muhammad Rayyan Malik**

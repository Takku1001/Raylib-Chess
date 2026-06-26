# Raylib-Chess

A fully graphical, two-player (hot-seat) chess game written in modern C++ using the [raylib](https://www.raylib.com/) graphics library. Built as an Object-Oriented Programming course project, it applies the four core OOP pillars — **encapsulation, inheritance, polymorphism, and abstraction** — to model the game cleanly: every chess piece is its own class derived from a common abstract base, and the board engine drives them through a shared interface.

## Features

- Complete chess rule set: legal move validation for every piece (pawn, knight, bishop, rook, queen, king)
- **Check, checkmate, and stalemate** detection
- **Pawn promotion** with an in-game selection dialog (Queen / Rook / Bishop / Knight)
- Click-to-select with **highlighted legal moves**, right-click to deselect
- Self-check prevention (a move that leaves your own king in check is rejected)

## Object-Oriented Design

The project is built around classic OOP principles:

- **Abstraction** — `Piece` is an abstract base class declaring a pure-virtual interface (`isLegalMove`, `move`, `Draw`) that every concrete piece must implement.
- **Inheritance** — `Pawn`, `Knight`, `Bishop`, `Rook`, `Queen`, and `King` each derive from `Piece`, reusing shared movement/path-checking helpers.
- **Polymorphism** — the `Board` stores pieces as `Piece*` and validates moves through virtual dispatch, so each piece enforces its own rules without the engine knowing the concrete type.
- **Encapsulation** — the 8×8 grid and capture state are private to `Board`; all access goes through well-defined member functions (`getPiece`, `movePiece`, `isCheck`, …).

## Tech Stack

| | |
|---|---|
| Language | C++17 |
| Graphics | raylib 5.5 (GLFW backend) |
| Build | Visual Studio 2022 / MSBuild (MSVC `v143`) |
| Dependencies | Managed via [vcpkg](https://vcpkg.io/) |
| Platform | Windows x64 |

## Project Structure

```
Raylib-Chess/
├── src/                       # Implementation (.cpp)
│   ├── BSAI24066_Project-3.cpp   # Entry point: window, rendering, input, promotion UI
│   ├── BSAI24066_Board.cpp       # Board engine: moves, undo, check/checkmate/stalemate
│   ├── BSAI24066_Piece.cpp       # Abstract base piece + shared move/path helpers
│   ├── BSAI24066_Pawn.cpp        # Per-piece movement rules
│   ├── BSAI24066_Knight.cpp
│   ├── BSAI24066_Bishop.cpp
│   ├── BSAI24066_Rook.cpp
│   ├── BSAI24066_Queen.cpp
│   ├── BSAI24066_King.cpp
│   └── BSAI24066_Header.cpp      # Console/utility helpers
├── include/                   # Header files (.h)
├── assets/                    # Board and piece sprites (PNG)
├── CHESS-3.sln                # Visual Studio solution
├── CHESS-3.vcxproj            # Project file
├── .gitignore
└── README.md
```

## Prerequisites

- **Windows 10/11 (x64)**
- **Visual Studio 2022** with the *Desktop development with C++* workload (MSVC v143)
- **vcpkg** with raylib installed:

  ```powershell
  git clone https://github.com/microsoft/vcpkg
  .\vcpkg\bootstrap-vcpkg.bat
  .\vcpkg\vcpkg install raylib:x64-windows
  .\vcpkg\vcpkg integrate install
  ```

  `vcpkg integrate install` enables automatic include/link/DLL deployment for the project — no manual paths required.

## How to Run

1. Clone the repository and install raylib via vcpkg (see above).
2. Open `CHESS-3.sln` in Visual Studio 2022.
3. Set the build configuration to **Debug** (or **Release**) and platform to **x64**.
4. Press **F5** (Start Debugging) or **Ctrl+F5** (Start Without Debugging).

> The game's working directory is the project root, so the sprites in `assets/` are loaded automatically.

## Controls

| Action | Input |
|---|---|
| Select a piece | Left-click (legal destinations are highlighted) |
| Move | Left-click the target square |
| Deselect | Right-click |
| Pawn promotion | Click an option, or press **1**–**4** (Queen / Rook / Bishop / Knight) |
| Quit | **Esc** |

## Author

**Muhammad Rayyan Malik**

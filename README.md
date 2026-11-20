# 🍬 Candy Tic-Tac-Toe

A colorful, playful two-player Tic-Tac-Toe game built with **C++17** and **SFML 3**.

## Features

- Pastel candy-inspired interface
- Mouse-click gameplay
- Two-player X and O mode
- Win and draw detection
- Score tracking for X and O
- Restart button and `R` keyboard shortcut
- Hover feedback on board cells and button
- `Esc` to quit

## Requirements

- Windows 10/11 (or another OS supported by SFML 3)
- Visual Studio 2022 with the Desktop development with C++ workload
- CMake 3.20 or newer
- SFML 3

## Build on Windows with vcpkg (recommended)

1. Install [vcpkg](https://github.com/microsoft/vcpkg) if you do not already have it.
2. Install SFML 3:

   ```powershell
   vcpkg install sfml:x64-windows
   ```

3. Open a terminal in this project folder and configure the project. Replace the vcpkg path with your actual vcpkg folder:

   ```powershell
   cmake -B build -S . -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
   ```

4. Build:

   ```powershell
   cmake --build build --config Release
   ```

5. Run `build/Release/CandyTicTacToe.exe`.

If CMake cannot find SFML, check that the toolchain path points to your vcpkg installation and that `sfml:x64-windows` installed successfully.

## Build with an existing SFML 3 installation

If SFML 3 is already installed in a custom folder, configure CMake with its package directory:

```powershell
cmake -B build -S . -A x64 -DCMAKE_PREFIX_PATH="C:/Libraries/SFML"
cmake --build build --config Release
```

The `CMAKE_PREFIX_PATH` should point to the SFML installation prefix that contains its `lib/cmake/SFML` package files. If your downloaded SFML archive has a different folder layout, use the folder that contains the SFML CMake package files.

## Font

The game looks for a font in this order:

1. `assets/arial.ttf`
2. `C:/Windows/Fonts/arial.ttf`
3. `C:/Windows/Fonts/segoeui.ttf`
4. `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf`

On Windows, Arial or Segoe UI is normally already available. For portability, you can add a redistributable font such as DejaVu Sans to `assets/arial.ttf` after checking and following that font's license.

## Controls

- Left-click an empty square to place your mark.
- Click **Play again** or press `R` to reset the board.
- Press `Esc` to close the game.

## Project structure

```text
Candy-Tic-Tac-Toe/
├── assets/
│   └── README.md
├── src/
│   └── main.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## GitHub

Create a new empty GitHub repository, then run these commands from this folder:

```bash
git init
git add .
git commit -m "Build Candy Tic-Tac-Toe with C++ and SFML 3"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/Candy-Tic-Tac-Toe.git
git push -u origin main
```

Replace `YOUR-USERNAME` with your GitHub username.

---

Made with C++ and a little candy-colored fun. 🍬

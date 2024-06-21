# 🦊 Untitled Fox Game 🦊

My personal hobby engine and game for practicing clean code, C, and OpenGL.

---

# 🏗️ Project Structure 🏗️
```sh
.
├── bin
│   └── # This is where the game goes.
├──[.sh/o/so]── # Arcane unstable personal build scripts and jank. Magic. Do not touch. 
└── src
    ├── main.c
    └── modules
        ├── ext
        │   ├── # Miscellaneous external .o|.h|.c files made by other people.
        │   └── # I try to use as few of these as I can.
        ├── tgl
        │   └── # "Tetra's GL", custom-built wrapper graphics library over OpenGL and GLFW.
        └── ttk
            └── # "Tetra's Toolkit", custom-built general-use macros and data structures.
```

---

# 🛠️ Build Process 🛠️
```sh
untitled-fox-game/
> sh release_build.sh
```

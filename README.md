# 🦊 Untitled Fox Game 🦊

My personal hobby engine and game for practicing clean code, C, and OpenGL.

Haven't decided on a build system yet so have fun with my unholy personal build scripts.

# 🏗️ Project Structure 🏗️
```sh
untitled-fox-game
├── bin
│   └── # This is where the game goes.
├──[.sh/o/so]── # Magic. Do not touch. 
└── src
    ├── main.c
    └── modules
        ├── external
        │   ├── # Misc external file for libraries made by other people.
        │   └── # I try to use as few of these as I reasonably can.
        ├── sdlext
        │   └── # My personal extensions to SDL.
        └── tooklit
            └── # General-use self-written stuffs.
```

# 🛠️ Build Process 🛠️
```sh
git clone https://github.com/tetraketra/untitled-fox-game
cd untitled-fox-game
sh ./debug.sh
```

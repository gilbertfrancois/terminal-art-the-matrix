# Simulating the Iconic Digital Rain Effect from "The Matrix" in C

_Gilbert François Duivesteijn_



## About

Welcome to an exploration of the iconic digital rain effect, inspired by the mesmerizing visuals from the renowned movie "The Matrix." In this program dives into the realm of C programming to recreate the enigmatic cascade of characters that captured the imagination of audiences worldwide.

The digital rain, a cascade of green characters raining down the screen, has become an emblematic symbol synonymous with futuristic aesthetics. Recreating this effect in C allows us to not only pay homage to a cinematic marvel but also delve into the artistry of programming. Through careful manipulation of terminal output, we simulate the immersive and captivating visual experience reminiscent of the Matrix's iconic scenes.

| ![macOS](assets/screenshots/macos.png) | ![Windows](assets/screenshots/windows.png) | ![Linux](assets/screenshots/linux2x.png) |
| -------------------------------------- | ------------------------------------------ | ---------------------------------------- |
| *iTerm on macOS*                       | *CMD on Windows*                           | *Terminal on Linux*                      |



## Leveraging xterm-Compatible Terminal Escape Codes for Colorful Effects

Terminal escape codes, especially those compatible with xterm, offer a powerful means to introduce colors and formatting into terminal-based applications. In C programming, you can utilize these escape codes to enhance the visual appeal of your digital rain effect or any terminal-based output.

For xterm-compatible terminals, you can employ ANSI escape codes, which are a standardized way to control text formatting, color, cursor movement, and other display options within the terminal.

To introduce colors using ANSI escape codes in C, you can incorporate specific sequences before the text you want to colorize. For instance, to change the text color to green, you'd use the escape code `"\033[32m"` before the text and `"\033[0m"` to reset the color back to default.



## Compatibility

This program boasts versatile compatibility, seamlessly running on a multitude of operating systems including macOS, Linux, and Windows. Its design is tailored to function effortlessly with nearly every standard C99 compiler available across these platforms. Whether compiling on macOS, Linux distributions, or Windows environments, this program ensures a consistent and reliable execution across diverse systems without compromise.



## Build and run

### Linux and macOS:

```
git clone https://github.com/gilbertfrancois/terminal-art-the-matrix.git
cd terminal-art-the-matrix

cmake -B build -S .
cmake --build build
cmake --install build

# Run:
cd dist
./matrix
```



### Windows with Visual Studio 2022:

- Clone the repository and open the folder as project.
- Cmake will automatically add the debug and install target.
- Choose from the menu **Build** -> **Build all**. The binary can be found in `<project_folder>/dist`.


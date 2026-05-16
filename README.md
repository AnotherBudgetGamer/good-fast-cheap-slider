# Good Fast Cheap Slider

Good Fast Cheap Slider is a small C/Raylib UI experiment built to demonstrate proportional value distribution across three linked sliders.

The project uses Raylib for windowing, input, and drawing, along with personal ABG helper libraries:

- `abg-core` for math helpers such as value remapping and clamping
- `abg-ui` for rectangle creation, rectangle collision checks, and simple drawing helpers

The current version focuses on a simple interactive slider system where the total value is always distributed across three categories:

```txt
GOOD + CHEAP + FAST = 100
```

Dragging one slider updates its value and proportionally redistributes the remaining value between the other sliders.

This project is intentionally simple and is meant to be easy to build, inspect, and expand.

## Table of Contents
- [Project Structure](#project-structure)
- [Important Files](#important-files)
- [Build Requirements](#build-requirements)
- [Dependencies](#dependencies)
- [Building with Make](#building-with-make)
- [Controls](#controls)
- [Linker Flags](#linker-flags)
- [Notes](#notes)
- [Future Improvements](#future-improvements)

## Project Structure
```
good-fast-cheap-slider/
├── Makefile
├── main.c
└── README.md
```

## Important Files
## Important Files

| File      | Purpose |
| :-------- | :------ |
| `Makefile` | Builds the demo executable |
| `main.c` | Contains the slider data, update logic, drawing code, and main loop |
| `README.md` | Project documentation |

## Build Requirements
You will need a C compiler, Raylib, and basic build tools.

### For Linux / WSL

Install build tools:
```Bash
sudo apt update
sudo apt install build-essential
```

This will give access to the following for this library:
```
gcc
make
```

## Dependencies
This project depends on:
```
raylib
abg-core
abg-ui
```
The source includes:
```
#include <raylib.h>
#include "abg_core.h"
#include "abg_ui.h"
```
### Raylib
Raylib handles:
```
window creation
mouse input
drawing
colors
main loop
```
### ABG Core
`abg-core` is used for math helpers, especially value remapping and clamping.

The current slider system uses:
```C
ABG_RemapFloatClamped(...)
```
That converts mouse Y position into a slider value between `0` and `100`.

### ABG UI
`abg-ui` is used for rectangle helpers and drawing wrappers.

The current slider uses helpers such as:
```
ABG_RectFromSize(...)
ABG_RectContainsPoint(...)
ABG_DrawRect(...)
ABG_DrawRectLines(...)
```
These are used to create rectangle sliders, detect hover state, draw filled bars, and draw outlines.

## Building with Make
From the project root:
```Bash
make
```
This builds:
```
main
```
To rebuild from scratch:
```Bash
make clean
make
```
To run after building:
```Bash
./main
```
## Controls
| Input                   |  Behavior                       |
| :-----                  |  :------                        |
| Move mouse over slider  |  Highlights hovered slider      |
| Left-click and drag     |  Changes selected slider value  |
| Release mouse           |  Stops dragging                 |
Sliders are updated live while dragging.

## Linker Flags
This project links against Raylib and the ABG helper libraries:
```bash
-labg_ui -labg_core -lraylib

On Linux, Raylib may also require additional system libraries:
```Bash
-lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXcursor
```

## Notes
This project is a small learning project focused on interactive UI behavior in C.

The main goal is to practice:
```
hover state
drag state
mouse input
value remapping
value clamping
proportional distribution
edge-case handling
simple UI drawing
```
This project is also a useful test program for the ABG C/Raylib helper libraries.

It demonstrates how small helpers from `abg-core` and `abg-ui` can be used together in a real interactive example without requiring a full UI framework.

## Future Improvements
Possible future improvements:
```
move slider logic into separate functions
move slider drawing into a Slider_Draw function
add a Slider_UpdateHover function
add a Slider_UpdateDrag function
add a Slider_GetTotal debug helper
add a reset button
add keyboard controls
add smoother visual styling
add text centering helpers
turn this into an abg-ui slider demo
eventually promote slider behavior into abg-ui itself
```

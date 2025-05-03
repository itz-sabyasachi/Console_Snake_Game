# snake with classes
# Classic Snake Game in C++
A lightweight, console-based implementation of the iconic Snake game built with native C++ and Windows APIs. Perfect for learning game loops, collision detection, and input handling in a terminal environment.

# How It Works
Game Loop: Uses a continuous loop with Sleep() for frame control (~120ms delay).

# Libraries Used
1) "<iostream>"
<br>
2) <vector>
 <br>
3) <cstdlib>
 <br>
4) <ctime>
 <br>
5) <windows.h>
 <br>
6) <conio.h>

# 1. Core Classes
# Snake Class

1)body: Stores segments as (x,y) pairs in a vector.

2)move(): Updates head position based on direction, shifts body.

3)grow(): Adds a segment without removing the tail (on eating food).

4)Input Handling: Uses _kbhit() + _getch() for WASD controls.

# Game Class

1)Game Loop: Runs at ~7 FPS (Sleep(120)).

2)Collision Checks:

// Wall collision
if (head.first <= 0 || head.first >= width - 1) → Game Over
<br>
// Self-collision
<br>
if (head == body[i]) → Game Over

3)Food System: Random spawns with rand(), avoids snake body.

# 2. Rendering Logic
Grid Drawing:

1)Borders (with Hashtag), Snake (O head / o body), Food (with asterisk).

2)Refreshes with system("cls") each frame.


# Snake Mechanics:

Grows when eating food (used asterisk symbol for this)

Dies on wall/self collisions

Direction changes via WASD input

Rendering: Dynamically redraws the grid (20x20 by default) with borders (using hashtags), snake (O), and food (with asterisk).

Score System: +10 point per food eaten

# Why These Libraries?
 <windows.h>: Required for Windows-specific console control (clearing screen, delays).
<br>
 <conio.h>: Lightweight alternative to heavier input libraries (like SFML).
<br>
 <vector>: Efficiently manages dynamic snake length.
<br>
 <cstdlib>: Simplifies random food placement.

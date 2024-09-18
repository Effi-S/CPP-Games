# Ex4: 6 Colors Game

## Overview:
This is a strategic game where two players (user vs CPU or two users) compete to claim the majority of a board by changing the color of connected shapes.

### Key Features:
- **Efficient Board Creation**: The board is generated in $O(n)$ time.
- **Game Modes**: Choose between single-player (vs CPU) or multiplayer modes.
- **Customizable**: Players can resize the map.

## Rules:
1. **Player 1** starts at the bottom-left, and **Player 2** (user or CPU) starts at the top-right. Both start colored black.
2. On each turn, a player picks a color from 6 options. All adjacent shapes of that color are claimed and recolored.
3. The game continues until a player controls 50% of the board.
4. Players cannot choose colors already in use by themselves or the opponent.

## Classes:

### `ShapeCell`:
- Manages a shape and its neighboring connections.
- Can merge with adjacent shapes of the same color.
- Randomly splits into triangles if it’s a square.

### `Board`:
- Holds the `ShapeCell` vector and manages the board layout.
- Efficiently constructed in O(n) time.

### `Controller`:
- Manages gameplay, player turns, and board rendering.
- Tracks board control percentage and declares the winner.
- Handles game settings, including board resizing and mode changes.

### `Player`:
- Base class for players, managing their claimed shapes and chosen color.

### `CPU` (Derived from `Player`):
- Uses a recursive algorithm to make optimal color choices based on neighboring cells.

### `Person` (Derived from `Player`):
- Accepts color choices from the user via the toolbar.

### `Toolbar`:
- Displays color options for players to choose from.
- Provides user input for turns and settings.

### `ImageLoader`:
- Singleton class for loading and accessing game images.

## Known Bugs:
- In multiplayer mode, the starting cell is not shaded correctly.

[back](../README.md)
# Bomberman

## Docker Build & Run
```bash
docker build -t bomberman .
docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --rm bomberman
```

## Game Overview
This is a Bomberman game where the player navigates through levels, planting bombs to defeat guards and uncover doors to progress. The player has 5 lives per level and must avoid bombs and guards while completing the level before time runs out.

## File Structure
- **Controller.cpp/h**: Controls the game.
- **LevelLoader.cpp/h**: Loads game levels.
- **Robot.cpp/h**: Robot class, derived from `Character`.
- **Guard.cpp/h**: Guard class, derived from `Character`.
- **DumbGuard.cpp/h**: Derived from `Placeable`, moves randomly.
- **SmartGuard.cpp/h**: Derived from `Placeable`, uses BFS for movement.
- **Bomb.cpp/h**: Handles bomb functionality.
- **Door.cpp/h**: Represents the door to the next level.
- **Stone.cpp/h**: Represents destructible stones.
- **Edge.cpp/h**: Represents indestructible edges.
- **Present.cpp/h**: Represents collectible items.
- **EmptyCell.cpp/h**: An empty cell on the map.
- **CONSTS.h**: Defines constants, structs, and enums.
- **Placeable.cpp/h**: Pure virtual base class.
- **Character.cpp/h**: Pure virtual base class, derived from `Placeable`.
- **highscore.txt**: Stores the high score.
- **board.txt**: Defines the game map, level settings, and symbols.

## Gameplay
- The player controls the Robot using arrow keys and can plant bombs with `B`.
- Guards move based on their type (random or smart) and can kill the player if they collide.
- The level ends when the player reaches the door, or if they lose all lives.
- A bomb explodes after 5 seconds, affecting surrounding cells. It can kill the player or guards and destroy stones.

## Object Interactions
- **Robot**: Moves with arrow keys, plants bombs, tries to find the door.
- **Guard**: Attempts to reach the player; respawns after being killed by a bomb.
- **Bomb**: Counts down from 5 before exploding, affecting nearby cells.
- **Door**: Moves the player to the next level when reached.
- **Stone**: Blocks movement, but can be destroyed by bombs.
- **Present**: Hidden inside stones, revealed upon destruction.
- **Edge**: Cannot be crossed or destroyed.

## Algorithms
- **SmartGuard**: Uses Breadth-First Search (BFS) to track the player.

### Known Bugs
- Bomb is not always displayed after hitting the Robot.
# CPP-Games
C++ Games from OOP Course (2019)

### Installation Steps: [here](#installation) 
## Bubble Struggle
This Is a game Where the player/s must avoid bouncing balls , that bounce all over the screen  the player can shoot the balls  only once all of the balls that are on the screen are gone can the player/s move on to the next level.
<br />
<img src="https://user-images.githubusercontent.com/57197982/164995253-eada288a-19b2-4630-b588-b558e1519175.png" width="400">
<img src="https://user-images.githubusercontent.com/57197982/164995507-5bac9978-4dd0-4a21-ab55-2e1d8c315b13.png" width="400">
<img src="https://user-images.githubusercontent.com/57197982/164995444-fb8cc3f2-8bb3-412d-b9bd-1f616f5fcffc.png" width="400">
<img src="https://user-images.githubusercontent.com/57197982/164995330-f30089b6-aa69-422e-b581-00596a15af5c.png" width="400">
## Bomberman
The 1983 classic Bomberman game re-designed/re-invented.
<br />
<img src="https://user-images.githubusercontent.com/57197982/164995874-d088706c-23f9-42db-9c43-910b97d89815.png" width="500">

## 6 Colors
Race against the computer to fill the board with your tiles
<br />
<img src="https://user-images.githubusercontent.com/57197982/164995966-a5e9bee5-4a5f-45c3-a537-c575b157029c.png" width="400">

## Installation:

### Docker 
All games have a `Dockerfile`.

In the top of each game's `README.md` you can find the docker commands to build and run

usually something like:
```
docker build -t image-name . && docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --rm image-name
```

### Ubuntu (or WSL)
Each game has a: `ubuntu-build.md` guide.

### Windows
All games have:
  1. Executable (`.exe`) in `/Release` folder   
  2. `.sln` file for opening with Visual Studios


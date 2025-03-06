MinesweeperQt - A Simple Minesweeper Game in C++ and Qt

Description:
MinesweeperQt is a classic Minesweeper game implemented in C++ using the Qt framework. The objective is to uncover all non-mine spaces while avoiding mines.

Features:
- 30x16 grid with 99 randomly placed mines
- Right-click functionality to cycle between flagging (🚩), marking with a question mark (?), and clearing the marking
- Recursive clearing of empty spaces when no adjacent mines are present
- Win and loss conditions with popups allowing the player to restart or exit
- Restart feature that resets the board with new random mines

Requirements:
To compile this project, you need:
    - Qt 5 or later installed
    - qmake and make (included with Qt development tools)
    - A Linux or macOS system (or Windows with MinGW/MSYS2)
    - C++ compiler (g++ or equivalent)
    - Compilation and Running Instructions:

To run this project:
    1. Navigate to the project folder:
        cd MinesweeperQt

    2. Generate the Makefile using qmake:
        qmake -r

        If qmake does not work, try:
            qmake-qt5 -r
        or specify the full path:
            /usr/lib/qt5/bin/qmake -r

    3. Compile the project using make:
        make

    4. Run the game:
        ./MinesweeperQt

        On Windows, run:
        MinesweeperQt.exe


Gameplay Instructions:
- Left-click: Reveal a cell
- Right-click: Cycle through:
- Flag (Marks as a mine)
- Question mark (Uncertain mine placement)
- Empty (Reverts to normal cell)
- Win Condition: Successfully uncover all non-mine spaces
- Lose Condition: Click on a mine
- Restarting: After losing or winning, a popup appears to either restart or exit


Project Structure:

    MinesweeperQt/
    │── src/ - Source code files (.cpp, .h)
    │── images/ - Minesweeper icons (mine, flag, question mark)
    │── resources.qrc - Qt resource file for embedded images
    │── MinesweeperQt.pro - Qt project file for qmake
    │── README.txt - Instructions on running the game
    │── Makefile - Generated after running qmake

Troubleshooting:

Icons not loading?
Ensure resources.qrc is correctly included in the build process:
qmake -r
make

If icons still don’t appear, check the .qrc file and confirm that images are in the images/ folder.

Compilation errors?
Try regenerating the Makefile:
qmake -r
make clean
make

Ensure Qt 5 is installed (qt5-default on Linux or brew install qt5 on macOS).

Game window not appearing?
Run the game from the project directory using:
./MinesweeperQt

(if having more issues, try running:
        qmake -r
        make clean
        qmake -r
        make
        ./MinesweeperQt
)
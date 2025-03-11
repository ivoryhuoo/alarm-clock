Rise and Pi - A Simple Alarm Clock in C++ and Qt


Features:
- Real Time Clock in hours, minutes and seconds
- Setting an alarm with a name and time (hours and minutes)
- Viewing a list of active alarms
- Snoozing an alarm for 5 minutes 

Requirements:
To compile this project, you need:
    - Qt 5 or later installed
    - qmake and make (included with Qt development tools)
    - A Linux or macOS system (or Windows with MinGW/MSYS2)
    - C++ compiler (g++ or equivalent)
    - Compilation and Running Instructions:

To run this project:
    1. Navigate to the project folder:
        cd group27

    2. Generate the Makefile using qmake:
        qmake -r

        If qmake does not work, try:
            qmake-qt5 -r
        or specify the full path:
            /usr/lib/qt5/bin/qmake -r

    3. Compile the project using make:
        make

    4. Run the game:
        ./Alarm

        On Windows, run:
        Alarm.exe


Use Instructions:


Project Structure:

    MinesweeperQt/
    │── src/ - Source code files (.cpp, .h)
    │── images/ - Minesweeper icons (mine, flag, question mark)
    │── resources.qrc - Qt resource file for embedded images
    │── MinesweeperQt.pro - Qt project file for qmake
    │── README.txt - Instructions on running the game
    │── Makefile - Generated after running qmake



(if having more issues, try running:
        qmake -r
        make clean
        qmake -r
        make
        ./Alarm
)
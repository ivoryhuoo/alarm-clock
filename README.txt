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
    - A Linux or macOS system (this program was created/tested on macOS)
    - C++ compiler (g++ or equivalent)
    - Compilation and Running Instructions:

To run this project:
    1. Navigate to the project folder:
        cd group27

    2. Generate the Makefile using qmake:
        qmake

    3. Compile the project using make:
        make

    4. Run the program:
        ./Alarm


Use Instructions:
1. Set an alarm by clicking "Set Alarm" and entering the time and label.
2. View all active alarms by clicking "View Alarms".
3. Snooze an alarm by selecting "Snooze" when it rings (delays by 5 minutes)
4. Dismiss an alarm completely by selecting "Dismiss".


Project Structure:

    Alarm/
    │── src/ - Source code files (.cpp)
    │── include/ - Header code files (.h)
    │── Alarm.pro - Qt project file for qmake
    │── README.txt - Instructions on running the game
    │── Makefile - Generated after running qmake
    │── main.cpp - Main function (entry point of the application) 
    │── resource.qrc - Qt resource collection file



(if having more issues, try running:
        make clean (clearing the executable file and recompiling the program)
)

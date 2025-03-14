/**
 * @file main.cpp
 * @brief Entry point for the Qt application.
 *
 * This file contains the main function, which initializes
 * the QApplication and displays the main window.
 * 
 * @author Group 27
 * @date Friday, March 14
 */

 #include <QApplication>
 #include "mainwindow.h"
 
 /**
  * @brief The main function of the application.
  *
  * This function initializes a QApplication instance, creates the main window,
  * displays it, and starts the event loop.
  *
  * @param argc The number of command-line arguments.
  * @param argv The array of command-line arguments.
  * @return The exit status of the application.
  */
 int main(int argc, char *argv[]) {
     QApplication app(argc, argv); ///< The main Qt application object.
     
     MainWindow mainWindow; ///< The main application window.
     mainWindow.show(); ///< Display the main window.
 
     return app.exec(); ///< Enter the Qt event loop.
 }
 
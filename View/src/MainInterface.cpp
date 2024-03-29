#include "MainInterface.h"

void MainInterface::mainMenuInterface()
{
    cout << "--------------------------------------------------------" << endl;
    cout << "MAIN MENU:" << endl;
    cout << "1. Go to your media files." << endl;
    cout << "2. Go to your playlists." << endl;
    cout << "3. Play music." << endl;
    cout << "0. Quit" << endl;
    cout << "Input your command: " << endl;
}

void MainInterface::invalidChoiceInterface()
{
    cout << "Invalid choice. Please try again." << endl;
}

void MainInterface::exitProgram()
{
    cout << "Exiting the application. Goodbye!" << endl;
}

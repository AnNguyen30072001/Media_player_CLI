#include "main.h"
#include "MainInterface.h"
#include "Playlist.h"
#include "MediaBrowser.h"

void MainInterface::mainMenuInterface() {
    cout << "--------------------------------------------------------" << endl;
    cout << "MAIN MENU:" << endl;
    cout << "1. Go to your media files" << endl;
    cout << "2. Go to your playlists" << endl;
    cout << "0. Quit" << endl;
    cout << "Input your command: ";
}

void MainInterface::invalidChoiceInterface() {
    cout << "Invalid choice. Please try again." << endl;
}

void MainInterface::exitProgram() {
    cout << "Exiting the application. Goodbye!" << endl;
}

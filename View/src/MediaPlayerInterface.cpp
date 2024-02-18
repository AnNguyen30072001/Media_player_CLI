#include "MediaPlayerInterface.h"

void MediaPlayerInterface::menuInterface()
{
    cout << "--------------------------------------------------------" << endl;
    cout << "MEDIA PLAYER MENU:" << endl;
    cout << "1. Play music from local files." << endl;
    cout << "2. Music player options." << endl;
    cout << "0. Back." << endl;
    cout << "Enter your command: " << endl;
}

void MediaPlayerInterface::loadFailed()
{
    cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
}

void MediaPlayerInterface::playFailed()
{
    cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << endl;
}

void MediaPlayerInterface::displayCurrentFileName(string name)
{
    cout << endl
         << "----------Now playing: " << name << "----------";
}

void MediaPlayerInterface::displayCurrentTime(int current_minute, int current_second,
                                              int duration_minute, int duration_second)
{
    // Move cursor to the beginning of the line
    cout << "\r";
    // Print the updated information
    cout << "Current Time: " << current_minute << ":" << current_second << " / "
         << duration_minute << ":" << duration_second << flush;
}

void MediaPlayerInterface::notPlayingNotice()
{
    cout << "Play some music first." << endl;
}

void MediaPlayerInterface::enterPlayOption()
{
    cout << "Enter option: (p)lay/pause, (n)ext, (b)ack, (v)olume, (s)top, (e)scape: " << endl;
}

void MediaPlayerInterface::resumeMusic()
{
    cout << "Resuming music..." << endl;
}

void MediaPlayerInterface::pauseMusic()
{
    cout << "Pausing music..." << endl;
}

void MediaPlayerInterface::changeVolume()
{
    cout << "Enter new volume (0-128): " << endl;
}

void MediaPlayerInterface::endPlaylist()
{
    cout << endl
         << "End playlist. Quitting music player now...." << endl;
}
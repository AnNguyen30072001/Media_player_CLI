#include "PlaylistInterface.h"
#include "Playlist.h"

void PlaylistInterface::menuInterface() {
    cout << "--------------------------------------------------------" << endl;
    cout << "PLAYLIST MENU:" << endl;
    cout << "1. View playlist." << endl;
    cout << "2. Create playlist." << endl;
    cout << "3. Delete playlist." << endl;
    cout << "4. Add file to playlist." << endl;
    cout << "5. Remove file from playlist." << endl;
    cout << "6. Metadata." << endl;
    cout << "0. Back." << endl;
    cout << "Enter your command: ";
}

void PlaylistInterface::viewPlaylist(vector<Playlist*> playlists) {
    int playlist_idx = 1;
    for (auto& playlist : playlists) {
        cout << playlist_idx << ". ";
        cout << "Playlist - " << playlist->getName() << endl;
        viewFilesInPlaylist(playlist);
        cout << endl;
        playlist_idx++;
    }
}

void PlaylistInterface::viewFilesInPlaylist(Playlist* playlist) {
    int file_idx = 1;
    for (auto& media_file : playlist->getFiles()) {
        cout << "    " << file_idx << ". ";
        cout << media_file.getName() << " - " << media_file.getPath() << endl;
        file_idx++;
    }
}

string PlaylistInterface::noPlaylistAvailable() {
    string command;
    cout << "There is no playlist available. Would you like to create new playlist (Y/N)?" << endl;
    getline(cin, command);
    return command;
}

void PlaylistInterface::enterPlaylistName(int input_case) {
    switch(input_case) {
        case CREATE_PLAYLIST:
            cout << "Enter name of new playlist: ";
            break;

        case DELETE_PLAYLIST:
            cout << "Enter index of playlist name that you want to delete: ";
            break;
        
        case ADD_TO_PLAYLIST:
            cout << "Enter index of playlist name that you want to add media file: ";
            break;

        case DELETE_FROM_PLAYLIST:
            cout << "Enter index of playlist name that you want to delete media file: ";
            break;

        case PLAYLIST_METADATA:
            cout << "Enter index of playlist name whose metadata you want to work with: ";
            break;

        default:
            cerr << "Error!" << endl;
    }
}

void PlaylistInterface::duplicateName(string name) {
    cout << "Playlist with name '" << name << "' has already existed." << endl;
}

void PlaylistInterface::playlistNotFound() {
    cout << "Playlist name not found!" << endl;
}

void PlaylistInterface::confirmAction(int input_case, string name) 
{
    switch(input_case) {
        case CREATE_PLAYLIST:
            cout << "Are you sure you want to create playlist named '" << name << "'? (Y/N): ";
            break;
        
        case DELETE_PLAYLIST:
            cout << "Are you sure you want to delete playlist named '" << name << "'? (Y/N): ";
            break;

        default:
            cerr << "Error!" << endl;
    }
}

void PlaylistInterface::createSuccessfully(string new_name) {
    cout << "New playlist - " << new_name << " - Created" << endl;
}

void PlaylistInterface::deleteSuccessfully(string playlist_name) {
    cout << "Playlist " << playlist_name << " has been deleted." << endl;
}
#ifndef __PLAYLIST_INTERFACE_
#define __PLAYLIST_INTERFACE_

#include "main.h"

class Playlist;

class PlaylistInterface
{
public:
    PlaylistInterface() = default;
    ~PlaylistInterface() = default;

    void menuInterface();

    void viewPlaylist(vector<Playlist *> playlists);

    void viewFilesInPlaylist(Playlist *playlist);

    string noPlaylistAvailable();

    void enterPlaylistName(int input_case);

    void duplicateName(string name);

    void playlistNotFound();

    void confirmAction(int input_case, string name);

    void createSuccessfully(string new_name);

    void deleteSuccessfully(string playlist_name);
};

#endif /* __PLAYLIST_INTERFACE_ */
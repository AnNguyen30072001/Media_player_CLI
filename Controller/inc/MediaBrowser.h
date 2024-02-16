#ifndef A9DD36C6_47EA_428A_86E9_2F094BE62ACE
#define A9DD36C6_47EA_428A_86E9_2F094BE62ACE

#include "main.h"
#include "MediaFile.h"
#include "MainInterface.h"
#include "MediaFileInterface.h"
#include "PlaylistInterface.h"
#include "Playlist.h"

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/taglib.h>

using namespace std;

class MediaBrowser {
private:
    vector<MediaFile*> mediaFiles;
    vector<Playlist*> playlists;
    MainInterface interface_main;
    MediaFileInterface interface_media_file;
    PlaylistInterface interface_playlist;
    MetadataInterface interface_metadata;
public:
    MediaBrowser();
    ~MediaBrowser();

    int captureInput();

    void localMediaFileBrowser();

    void playlistBrowser();

    void playlistMetadata();

    void mainProgram();

    void loadMediaFiles(const string& directory);

    void modifyMediaFiles();

    void createPlaylist();

    void addToPlaylist();

    void deleteFromPlaylist(Playlist* playlist);

    void deletePlaylist(int playlist_idx);

    void viewMetadata(int file_idx);

    void updateMetadata(int file_idx);

    vector<MediaFile*> getMediaFiles();

    vector<Playlist*> getPlaylists();
};

#endif /* A9DD36C6_47EA_428A_86E9_2F094BE62ACE */

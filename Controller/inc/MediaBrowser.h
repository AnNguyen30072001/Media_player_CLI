#ifndef A9DD36C6_47EA_428A_86E9_2F094BE62ACE
#define A9DD36C6_47EA_428A_86E9_2F094BE62ACE

#include "main.h"
#include "MediaFile.h"
#include "AudioFile.h"
#include "MainInterface.h"
#include "MediaFileInterface.h"
#include "PlaylistInterface.h"
#include "MediaPlayerInterface.h"
#include "Playlist.h"
#include "Metadata.h"
#include "MediaPlayer.h"

class MediaBrowser {
private:
    vector<MediaFile*> mediaFiles;
    vector<AudioFile*> audioFiles;
    vector<Playlist*> playlists;

    Metadata metadata;
    MediaPlayer mediaPlayer;

    MainInterface interface_main;
    MediaFileInterface interface_media_file;
    PlaylistInterface interface_playlist;
    MetadataInterface interface_metadata;
    MediaPlayerInterface interface_music_player;
public:
    MediaBrowser();
    ~MediaBrowser();

    int captureInput();

    void localMediaFileBrowser();

    int emptyPlaylistHandler();

    void playlistBrowser();

    void musicBrowser();

    void playlistMetadata();

    void mainProgram();

    void loadMediaFiles(const string& directory);

    void modifyMediaFiles();

    void createPlaylist();

    void addToPlaylist();

    void deleteFromPlaylist(Playlist* playlist);

    void deletePlaylist(int playlist_idx);

    vector<MediaFile*> getMediaFiles();

    vector<AudioFile*> getAudioFiles();

    vector<Playlist*> getPlaylists();
};

#endif /* A9DD36C6_47EA_428A_86E9_2F094BE62ACE */

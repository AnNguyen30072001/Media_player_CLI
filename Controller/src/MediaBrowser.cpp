#include "MediaBrowser.h"
#include "AudioFile.h"
#include "VideoFile.h"

#define START_PAGE 1
#define PAGINATION_SIZE 25
#define MP3_EXTENSION_NAME ".mp3"
#define MP4_EXTENSION_NAME ".mp4"

using namespace std;
namespace fs = filesystem;

MediaBrowser::MediaBrowser()
{
    loadMediaFiles(fs::current_path().string());
}

MediaBrowser::~MediaBrowser()
{
    for (auto &playlist : playlists)
    {
        delete playlist;
    }

    for (auto &mediaFile : mediaFiles)
    {
        delete mediaFile;
    }
}

int MediaBrowser::captureInput()
{
    int input_command;
    cin >> input_command;
    cin.ignore();
    return input_command;
}

void MediaBrowser::localMediaFileBrowser()
{
    int currentPage = START_PAGE;
    const int pageSize = PAGINATION_SIZE;
    int command;
    while (true)
    {
        interface_media_file.menuInterface();
        command = captureInput();
        switch (command)
        {
        case LIST_ALL_LOCAL_MEDIA_FILES:
            if (mediaFiles.empty())
            {
                interface_media_file.listEmpty();
                continue;
            }
            interface_media_file.displayMediaFiles(this, currentPage, pageSize);
            break;
        case MODIFY_MEDIA_FILE:
            modifyMediaFiles();
            break;

        case BACK:
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

int MediaBrowser::emptyPlaylistHandler()
{
    string create_playlist_cmd = interface_playlist.noPlaylistAvailable();
    if (create_playlist_cmd == "Y" || create_playlist_cmd == "y")
    {
        createPlaylist();
        return CONTINUE_ACTION;
    }
    else
    {
        return ABORT_ACTION;
    }
}

void MediaBrowser::playlistBrowser()
{
    int command;
    string create_playlist_cmd;
    string playlist_name;
    int playlist_idx;
    while (true)
    {
        interface_playlist.menuInterface();
        command = captureInput();
        switch (command)
        {
        case VIEW_PLAYLIST:
            if (playlists.empty())
            {
                if (emptyPlaylistHandler() == ABORT_ACTION)
                {
                    continue;
                }
            }
            interface_playlist.viewPlaylist(playlists);
            break;
        case CREATE_PLAYLIST:
            createPlaylist();
            break;

        case DELETE_PLAYLIST:
            if (playlists.empty())
            {
                continue;
            }
            interface_playlist.viewPlaylist(playlists);
            interface_playlist.enterPlaylistName(DELETE_PLAYLIST);

            playlist_idx = captureInput();
            if (playlist_idx > 0 && playlist_idx <= (int)playlists.size())
            {
                deletePlaylist(playlist_idx - 1);
            }
            else
            {
                interface_main.invalidChoiceInterface();
            }
            break;

        case ADD_TO_PLAYLIST:
            if (playlists.empty())
            {
                if (emptyPlaylistHandler() == ABORT_ACTION)
                {
                    continue;
                }
            }
            addToPlaylist();
            break;

        case DELETE_FROM_PLAYLIST:
            interface_playlist.viewPlaylist(playlists);
            interface_playlist.enterPlaylistName(DELETE_FROM_PLAYLIST);
            playlist_idx = captureInput();
            if (playlist_idx > 0 && playlist_idx <= (int)playlists.size())
            {
                deleteFromPlaylist(playlists[playlist_idx - 1]);
            }
            else
            {
                interface_playlist.playlistNotFound();
            }
            break;

        case PLAYLIST_METADATA:
            playlistMetadata();
            break;

        case BACK:
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::musicBrowser()
{
    thread music_thread;
    int input_command;
    int file_idx;
    string file_path;
    while (true)
    {
        interface_music_player.menuInterface();

        input_command = captureInput();
        switch (input_command)
        {
        case PLAY_MUSIC:
            interface_media_file.displayAudioFiles(this, START_PAGE, PAGINATION_SIZE);
            interface_media_file.enterMediaFileName(MUSIC_PLAYER);
            file_idx = captureInput();
            if (file_idx <= 0 || file_idx > (int)audioFiles.size())
            {
                interface_main.invalidChoiceInterface();
                continue;
            }

            mediaPlayer.forceStopMusic();
            /* Delay to wait for music thread to quit */
            while (mediaPlayer.isPlaying())
            {
            }
            mediaPlayer.resetForceStopFlag();

            music_thread = thread(MediaPlayer::playMusic, audioFiles, file_idx - 1);
            music_thread.detach();

            break;

        case MUSIC_PLAYER_OPTIONS:
            mediaPlayer.playOption();
            break;

        case BACK:
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::playlistMetadata()
{
    int metadata_cmd;
    int playlist_idx;
    int file_idx;
    while (true)
    {
        interface_metadata.menuInterface();
        metadata_cmd = captureInput();
        switch (metadata_cmd)
        {
        case SHOW_METADATA:
            if (playlists.empty())
            {
                interface_metadata.listEmpty(SHOW_METADATA);
                return;
            }
            interface_playlist.viewPlaylist(playlists);
            interface_playlist.enterPlaylistName(PLAYLIST_METADATA);

            playlist_idx = captureInput();
            if (playlist_idx <= 0 || playlist_idx > (int)playlists.size())
            {
                interface_main.invalidChoiceInterface();
                continue;
            }
            if (playlists[playlist_idx - 1]->getFiles().empty())
            {
                interface_metadata.listEmpty(SHOW_METADATA);
                return;
            }
            interface_playlist.viewFilesInPlaylist(playlists[playlist_idx - 1]);
            interface_metadata.metadataChooseFile(SHOW_METADATA);

            file_idx = captureInput();
            if (file_idx > 0 && file_idx <= (int)playlists[playlist_idx - 1]->getFiles().size())
            {
                bool file_found = false;
                int local_media_file_idx = 1;
                string file_name = playlists[playlist_idx - 1]->getFiles()[file_idx - 1].getName();
                for (const auto &local_file : mediaFiles)
                {
                    if (file_name == local_file->getName())
                    {
                        file_idx = local_media_file_idx;
                        file_found = true;
                        break;
                    }
                    local_media_file_idx++;
                }
                if (file_found == true)
                    metadata.viewMetadata(this, file_idx);
                else
                    interface_metadata.getMetadataError();
            }
            else
            {
                interface_main.invalidChoiceInterface();
            }
            break;

        case UPDATE_METADATA:
            if (playlists.empty())
            {
                interface_metadata.listEmpty(UPDATE_METADATA);
                return;
            }
            interface_playlist.viewPlaylist(playlists);
            interface_playlist.enterPlaylistName(PLAYLIST_METADATA);

            playlist_idx = captureInput();
            if (playlist_idx <= 0 || playlist_idx > (int)playlists.size())
            {
                interface_main.invalidChoiceInterface();
                continue;
            }
            if (playlists[playlist_idx - 1]->getFiles().empty())
            {
                interface_metadata.listEmpty(UPDATE_METADATA);
                return;
            }
            interface_playlist.viewFilesInPlaylist(playlists[playlist_idx - 1]);
            interface_metadata.metadataChooseFile(UPDATE_METADATA);

            file_idx = captureInput();
            if (file_idx > 0 && file_idx <= (int)playlists[playlist_idx - 1]->getFiles().size())
            {
                metadata.viewMetadata(this, file_idx);
                metadata.updateMetadata(this, file_idx);
            }
            else
            {
                interface_main.invalidChoiceInterface();
            }
            break;

        case BACK:
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::mainProgram()
{
    int menu_command;

    while (true)
    {
        interface_main.mainMenuInterface();
        menu_command = captureInput();

        switch (menu_command)
        {
        case GO_TO_MEDIA_FILES:
            localMediaFileBrowser();
            break;

        case GO_TO_PLAYLISTS:
            playlistBrowser();
            break;

        case MUSIC_PLAYER:
            musicBrowser();
            break;

        case EXIT_APPLICATION:
            interface_main.exitProgram();
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::loadMediaFiles(const string &directory)
{
    for (const auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            string fileExtension = entry.path().extension().string();
            transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

            if (fileExtension == MP3_EXTENSION_NAME)
            {
                mediaFiles.push_back(new AudioFile(entry.path().filename().string(), entry.path().string()));
                audioFiles.push_back(new AudioFile(entry.path().filename().string(), entry.path().string()));
            }

            if (fileExtension == MP4_EXTENSION_NAME)
            {
                mediaFiles.push_back(new VideoFile(entry.path().filename().string(), entry.path().string()));
            }
        }
    }
}

void MediaBrowser::modifyMediaFiles()
{
    int modify_command;
    int input_opt;
    string playlist_name;
    int currentPage = START_PAGE;
    int pageSize = PAGINATION_SIZE;

    while (true)
    {
        interface_media_file.modifyMenuInterface();

        modify_command = captureInput();
        string create_playlist_cmd;
        switch (modify_command)
        {
        case SHOW_METADATA:
            if (mediaFiles.empty())
            {
                interface_metadata.listEmpty(SHOW_METADATA);
                return;
            }
            interface_media_file.displayMediaFiles(this, currentPage, pageSize);
            interface_metadata.metadataChooseFile(SHOW_METADATA);

            input_opt = captureInput();
            metadata.viewMetadata(this, input_opt);
            break;

        case UPDATE_METADATA:
            if (mediaFiles.empty())
            {
                interface_metadata.listEmpty(UPDATE_METADATA);
                return;
            }
            interface_media_file.displayMediaFiles(this, currentPage, pageSize);
            interface_metadata.metadataChooseFile(UPDATE_METADATA);

            input_opt = captureInput();
            metadata.viewMetadata(this, input_opt);
            metadata.updateMetadata(this, input_opt);
            break;

        case ADD_LOCAL_TO_PLAYLIST:
            if (playlists.empty())
            {
                if (emptyPlaylistHandler() == ABORT_ACTION)
                {
                    continue;
                }
            }
            addToPlaylist();
            break;

        case BACK:
            return;

        default:
            interface_main.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::createPlaylist()
{
    string new_name;
    string confirm_action;
    interface_playlist.enterPlaylistName(CREATE_PLAYLIST);

    getline(cin, new_name);
    for (const auto &playlist : playlists)
    {
        if (playlist->getName() == new_name)
        {
            interface_playlist.duplicateName(new_name);
            return;
        }
    }
    interface_playlist.confirmAction(CREATE_PLAYLIST, new_name);

    getline(cin, confirm_action);
    if (confirm_action == "Y" || confirm_action == "y")
    {
        playlists.push_back(new Playlist(new_name));
        interface_playlist.createSuccessfully(new_name);
    }
}

void MediaBrowser::addToPlaylist()
{
    int playlist_idx;
    int file_idx;
    int currentPage = START_PAGE;
    int pageSize = PAGINATION_SIZE;

    interface_playlist.viewPlaylist(playlists);
    interface_playlist.enterPlaylistName(ADD_TO_PLAYLIST);

    playlist_idx = captureInput();
    if (playlist_idx > 0 && playlist_idx <= (int)playlists.size())
    {
        interface_media_file.displayMediaFiles(this, currentPage, pageSize);
        interface_media_file.enterMediaFileName(ADD_TO_PLAYLIST);
        file_idx = captureInput();
        if (file_idx > 0 && file_idx <= (int)mediaFiles.size())
        {
            for (auto &file_in_playlist : playlists[playlist_idx - 1]->getFiles())
            {
                if (file_in_playlist.getName() == mediaFiles[file_idx - 1]->getName())
                {
                    interface_media_file.duplicateFile();
                    return;
                }
            }
            playlists[playlist_idx - 1]->addFile(mediaFiles[file_idx - 1]);
            interface_media_file.fileAddSuccess();
        }
        else
        {
            interface_media_file.fileAddError();
        }
    }
    else
    {
        interface_main.invalidChoiceInterface();
    }
}

void MediaBrowser::deleteFromPlaylist(Playlist *playlist)
{
    if (playlist->getFiles().empty())
    {
        return;
    }
    int file_idx;

    interface_playlist.viewFilesInPlaylist(playlist);
    interface_media_file.enterMediaFileName(DELETE_FROM_PLAYLIST);

    file_idx = captureInput();
    vector<MediaFile> media_files = playlist->getFiles();
    string file_name = media_files[file_idx - 1].getName();
    if (file_idx > 0 && file_idx <= (int)media_files.size())
    {
        playlist->deleteFile(file_idx - 1);
        interface_media_file.fileDeleteSuccess(file_name);
    }
    else
    {
        interface_media_file.fileDeleteError();
    }
}

void MediaBrowser::deletePlaylist(int playlist_idx)
{
    string confirm_action;
    string playlist_name = playlists[playlist_idx]->getName();
    interface_playlist.confirmAction(DELETE_PLAYLIST, playlist_name);

    getline(cin, confirm_action);
    if (confirm_action == "Y" || confirm_action == "y")
    {
        playlists[playlist_idx]->getFiles().clear();
        delete playlists[playlist_idx];
        playlists.erase(playlists.begin() + playlist_idx);
        interface_playlist.deleteSuccessfully(playlist_name);
    }
}

vector<MediaFile *> MediaBrowser::getMediaFiles()
{
    return mediaFiles;
}

vector<AudioFile *> MediaBrowser::getAudioFiles()
{
    return audioFiles;
}

vector<Playlist *> MediaBrowser::getPlaylists()
{
    return playlists;
}
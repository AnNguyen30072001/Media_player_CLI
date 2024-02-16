#include "main.h"

#include "MediaBrowser.h"
#include <filesystem>

#define START_PAGE          1
#define PAGINATION_SIZE     10

using namespace std;
namespace fs = filesystem;

MediaBrowser::MediaBrowser() {
    loadMediaFiles(fs::current_path().string());
}

MediaBrowser::~MediaBrowser() {
    for(auto& playlist : playlists) {
        delete playlist;
    }

    for(auto& mediaFile : mediaFiles) {
        delete mediaFile;
    }
}

int MediaBrowser::captureInput() {
    int input_command;
    cin >> input_command;
    cin.ignore();
    return input_command;
}

void MediaBrowser::localMediaFileBrowser() {
    int currentPage = START_PAGE;
    const int pageSize = PAGINATION_SIZE;
    int command;
    while (true) {
        mediaFileInterface.menuInterface();
        command = captureInput();
        switch(command) {
            case LIST_ALL_LOCAL_MEDIA_FILES:
                mediaFileInterface.displayMediaFiles(this, currentPage, pageSize);
                break;
            case MODIFY_MEDIA_FILE:
                modifyMediaFiles();
                break;
            
            case BACK:
                return;

            default:
                interface.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::playlistBrowser() {
    // bool playlist_found;
    int command;
    string create_playlist_cmd;
    string playlist_name;
    int playlist_idx;
    while (true) {
        // playlist_found = false;
        playlistInterface.menuInterface();
        command = captureInput();
        switch(command) {
            case VIEW_PLAYLIST:
                if(playlists.empty()) {
                    create_playlist_cmd = playlistInterface.noPlaylistAvailable();
                    if(create_playlist_cmd == "Y" || create_playlist_cmd == "y") {
                        createPlaylist();
                    }
                    else {
                        continue;
                    }
                }
                playlistInterface.viewPlaylist(playlists);
                break;
            case CREATE_PLAYLIST:
                createPlaylist();
                break;

            case DELETE_PLAYLIST:
                if(playlists.empty()) {
                    continue;
                }
                playlistInterface.viewPlaylist(playlists);
                playlistInterface.enterPlaylistName(DELETE_PLAYLIST);

                playlist_idx = captureInput();
                if(playlist_idx > 0 && playlist_idx <= playlists.size()) {
                    deletePlaylist(playlist_idx - 1);
                }
                else {
                    playlistInterface.playlistNotFound();
                }
                

                // getline(cin, playlist_name);
                // for(auto& playlist : playlists) {
                //     if(playlist->getName() == playlist_name) {
                //         deletePlaylist(playlist_name);
                //         playlist_found = true;
                //         break;
                //     }
                // }
                // if(playlist_found == false) {
                //     playlistInterface.playlistNotFound();
                // }
                break;
            
            case ADD_TO_PLAYLIST:
                if(playlists.empty()) {
                    create_playlist_cmd = playlistInterface.noPlaylistAvailable();
                    if(create_playlist_cmd == "Y" || create_playlist_cmd == "y") {
                        createPlaylist();
                        playlistInterface.viewPlaylist(playlists);
                    }
                    else {
                        continue;
                    }
                }
                addToPlaylist();
                break;
            
            case DELETE_FROM_PLAYLIST:
                playlistInterface.viewPlaylist(playlists);
                playlistInterface.enterPlaylistName(DELETE_FROM_PLAYLIST);
                playlist_idx = captureInput();
                if(playlist_idx > 0 && playlist_idx <= (int)playlists.size()) {
                    deleteFromPlaylist(playlists[playlist_idx - 1]);
                }
                else {
                    playlistInterface.playlistNotFound();
                }
                break;

            case PLAYLIST_METADATA:
                playlistMetadata();
                break;
            
            case BACK:
                return;

            default:
                interface.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::playlistMetadata() {
    int metadata_cmd;
    int playlist_idx;
    int file_idx;
    while(true) {
        cout << "--------------------------------------------------------" << endl;
        cout << "METADATA MENU:" << endl;
        cout << "1. Show metadata." << endl;
        cout << "2. Update metadata." << endl;
        cout << "0. Back." << endl;
        metadata_cmd = captureInput();
        switch(metadata_cmd) {
            case SHOW_METADATA:
                if(playlists.empty()) {
                    return;
                }
                playlistInterface.viewPlaylist(playlists);
                playlistInterface.enterPlaylistName(PLAYLIST_METADATA);
                playlist_idx = captureInput();
                if(playlists[playlist_idx - 1]->getFiles().empty()) {
                    return;
                }
                playlistInterface.viewFilesInPlaylist(playlists[playlist_idx - 1]);
                mediaFileInterface.metadataChooseFile(SHOW_METADATA);
                file_idx = captureInput();
                if(file_idx > 0 && file_idx <= (int)playlists[playlist_idx - 1]->getFiles().size()){
                    viewMetadata(file_idx);
                }
                else {
                    interface.invalidChoiceInterface();
                }
                break;
            
            case UPDATE_METADATA:
                if(playlists.empty()) {
                    return;
                }
                playlistInterface.viewPlaylist(playlists);
                playlistInterface.enterPlaylistName(PLAYLIST_METADATA);
                playlist_idx = captureInput();
                if(playlists[playlist_idx - 1]->getFiles().empty()) {
                    return;
                }
                playlistInterface.viewFilesInPlaylist(playlists[playlist_idx - 1]);
                mediaFileInterface.metadataChooseFile(UPDATE_METADATA);
                file_idx = captureInput();
                if(file_idx > 0 && file_idx <= (int)playlists[playlist_idx - 1]->getFiles().size()){
                    viewMetadata(file_idx);
                    updateMetadata(file_idx);
                }
                else {
                    interface.invalidChoiceInterface();
                }
                break;

            case BACK:
                return;

            default:
                interface.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::mainProgram() {
    int menu_command;

    while (true) {
        interface.mainMenuInterface();
        menu_command = captureInput();

        switch (menu_command) {
            case GO_TO_MEDIA_FILES:
                localMediaFileBrowser();
                break;
            
            case GO_TO_PLAYLISTS:
                playlistBrowser();
                break;

            case EXIT_APPLICATION:
                interface.exitProgram();
                return;

            default:
                interface.invalidChoiceInterface();
        }
    }
}

void MediaBrowser::loadMediaFiles(const string& directory) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            string fileExtension = entry.path().extension().string();
            transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
            
            if (fileExtension == ".mp3") {
                mediaFiles.push_back(new AudioFile(entry.path().filename().string(), entry.path().string()));
            }

            if (fileExtension == ".mp4") {
                mediaFiles.push_back(new VideoFile(entry.path().filename().string(), entry.path().string()));
            }
        }
    }
}

void MediaBrowser::modifyMediaFiles() {
    int modify_command;
    int input_opt;
    string playlist_name;
    int currentPage = START_PAGE;
    int pageSize = PAGINATION_SIZE;

    while (true) {
        mediaFileInterface.modifyMenuInterface();
        modify_command = captureInput();
        string create_playlist_cmd;
        switch(modify_command) {
            case SHOW_METADATA:
                mediaFileInterface.displayMediaFiles(this, currentPage, pageSize);
                mediaFileInterface.metadataChooseFile(SHOW_METADATA);
                input_opt = captureInput();
                viewMetadata(input_opt);
                break;
            
            case UPDATE_METADATA:
                mediaFileInterface.displayMediaFiles(this, currentPage, pageSize);
                mediaFileInterface.metadataChooseFile(UPDATE_METADATA);
                input_opt = captureInput();
                viewMetadata(input_opt);
                updateMetadata(input_opt);
                break;

            case ADD_LOCAL_TO_PLAYLIST:
                if(playlists.empty()) {
                    create_playlist_cmd = playlistInterface.noPlaylistAvailable();
                    if(create_playlist_cmd == "Y" || create_playlist_cmd == "y") {
                        createPlaylist();
                    }
                    else {
                        continue;
                    }
                }
                addToPlaylist();             
                break;

            case BACK:
                return;

            default:
                interface.invalidChoiceInterface();
        }
    }
    
}

void MediaBrowser::createPlaylist() {
    string new_name;
    string confirm_action;
    playlistInterface.enterPlaylistName(CREATE_PLAYLIST);
    getline(cin, new_name);
    for(const auto& playlist : playlists) {
        if(playlist->getName() == new_name) {
            playlistInterface.duplicateName(new_name);
            return;
        }
    }
    playlistInterface.confirmAction(CREATE_PLAYLIST, new_name);
    getline(cin, confirm_action);
    if(confirm_action == "Y" || confirm_action == "y") {
        playlists.push_back(new Playlist(new_name));
        playlistInterface.createSuccessfully(new_name);
    }
}

void MediaBrowser::addToPlaylist() {
    int playlist_idx;
    int file_idx;
    int currentPage = START_PAGE;
    int pageSize = PAGINATION_SIZE;

    playlistInterface.viewPlaylist(playlists);
    playlistInterface.enterPlaylistName(ADD_TO_PLAYLIST);
    playlist_idx = captureInput();
    if(playlist_idx > 0 && playlist_idx <= (int)playlists.size()) {
        mediaFileInterface.displayMediaFiles(this, currentPage, pageSize);
        mediaFileInterface.enterMediaFileName(ADD_TO_PLAYLIST);
        file_idx = captureInput();
        if(file_idx > 0 && file_idx <= (int)mediaFiles.size()) {
            for(auto& file_in_playlist : playlists[playlist_idx-1]->getFiles()) {
                if(file_in_playlist.getName() == mediaFiles[file_idx-1]->getName()) {
                    mediaFileInterface.duplicateFile();
                    return;
                }
            }
            playlists[playlist_idx - 1]->addFile(mediaFiles[file_idx - 1]);
            mediaFileInterface.fileAddSuccess();
        }
        else {
            mediaFileInterface.fileAddError();
        }
    }
    else {
        playlistInterface.playlistNotFound();
    } 
}

void MediaBrowser::deleteFromPlaylist(Playlist* playlist) {
    if(playlist->getFiles().empty()) {
        return;
    }
    int file_idx;
    
    playlistInterface.viewFilesInPlaylist(playlist);
    mediaFileInterface.enterMediaFileName(DELETE_FROM_PLAYLIST);
    
    file_idx = captureInput();
    vector<MediaFile> media_files = playlist->getFiles();
    string file_name = media_files[file_idx-1].getName();
    if(file_idx > 0 && file_idx <= (int)media_files.size()) {
        playlist->deleteFile(file_idx - 1);
        mediaFileInterface.fileDeleteSuccess(file_name);
    }
    else {
        mediaFileInterface.fileDeleteError();
    }
}

void MediaBrowser::deletePlaylist(int playlist_idx) {
    string confirm_action;
    string playlist_name = playlists[playlist_idx]->getName();
    playlistInterface.confirmAction(DELETE_PLAYLIST, playlist_name);
    getline(cin, confirm_action);
    if(confirm_action == "Y" || confirm_action == "y") {
        playlists[playlist_idx]->getFiles().clear();
        delete playlists[playlist_idx];
        playlists.erase(playlists.begin() + playlist_idx);
        playlistInterface.deleteSuccessfully(playlist_name);
        // auto it = find_if(playlists.begin(), playlists.end(), 
        // [playlist_name](auto& playlist) {
        //     return playlist->getName() == playlist_name;
        // });
        // if(it != playlists.end()) {
        //     (*it)->getFiles().clear();
        //     delete *it;
        //     playlists.erase(it);
        //     playlistInterface.deleteSuccessfully(playlist_name);
        // }
    }
}

void MediaBrowser::viewMetadata(int file_idx) {
    string file_name = mediaFiles[file_idx-1]->getName();
    string file_path = mediaFiles[file_idx-1]->getPath();
    int file_type = mediaFiles[file_idx-1]->getType();
    TagLib::FileRef fileRef(file_path.c_str());
    if (!fileRef.isNull() && fileRef.tag()) {
        TagLib::Tag *tag = fileRef.tag();
        switch(file_type) {
        case AUDIO_FILE_TYPE:
            mediaFileInterface.displayAudioFileMetadata(tag, fileRef);
            break;
        case VIDEO_FILE_TYPE:
            mediaFileInterface.displayVideoFileMetadata(tag, fileRef, file_path);
            break;
        default:
            mediaFileInterface.getMediaFileTypeError();
        }
    } 
    else {
        mediaFileInterface.getMetadataError();
    }
}

void MediaBrowser::updateMetadata(int file_idx) {
    int update_opt;
    string new_value;
    cout << "Choose a metadata field to modify: ";
    update_opt = captureInput();
    cout << "Enter new value: ";
    getline(cin, new_value);
    string file_name = mediaFiles[file_idx-1]->getName();
    string file_path = mediaFiles[file_idx-1]->getPath();
    int file_type = mediaFiles[file_idx-1]->getType();
    TagLib::FileRef fileRef(file_name.c_str());
    TagLib::Tag *tag = fileRef.tag();
    if(file_type == AUDIO_FILE_TYPE) {
        switch(update_opt) {
        case MODIFY_TRACK:
            tag->setTrack(stoi(new_value));
            break;
        case MODIFY_ALBUM:
            tag->setAlbum(new_value.c_str());
            break;
        case MODIFY_ARTIST:
            tag->setArtist(new_value.c_str());
            break;
        case MODIFY_YEAR:
            tag->setYear(stoi(new_value));
            break;
        case MODIFY_GENRE:
            tag->setGenre(new_value.c_str());
            break;
        case MODIFY_AUDIO_DURATION:
            mediaFileInterface.modifyMetadataError();
            return;
        default:
            interface.invalidChoiceInterface();
        }
    }

    else {
        switch(update_opt) {
        case MODIFY_VIDEO_NAME:
            tag->setTitle(new_value.c_str());
            break;
        case MODIFY_SIZE:
            mediaFileInterface.modifyMetadataError();
            return;
        case MODIFY_BIT_RATE:
            mediaFileInterface.modifyMetadataError();
            return;
        case MODIFY_VIDEO_DURATION:
            mediaFileInterface.modifyMetadataError();
            return;
        default:
            interface.invalidChoiceInterface();
        }            
    }
    if(fileRef.save() == true) {
        mediaFileInterface.modifyMetadataSuccess();
    }
}

vector<MediaFile*> MediaBrowser::getMediaFiles() {
    return mediaFiles;
}

vector<Playlist*> MediaBrowser::getPlaylists() {
    return playlists;
}
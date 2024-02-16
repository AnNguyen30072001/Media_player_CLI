#include "MediaFile.h"
#include "Playlist.h"

void Playlist::addFile(MediaFile* file) {
    files.push_back(*file);
}

void Playlist::deleteFile(int file_idx) {
    files.erase(files.begin() + file_idx);
}

string Playlist::getName() {
    return name;
}

vector<MediaFile> Playlist::getFiles() {
    return files;
}
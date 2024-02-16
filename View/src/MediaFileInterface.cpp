#include "MediaFileInterface.h"
#include "MediaBrowser.h"

void MediaFileInterface::menuInterface() {
    cout << "--------------------------------------------------------" << endl;
    cout << "LOCAL MEDIA MENU:" << endl;
    cout << "1. List all local media files." << endl;
    cout << "2. Modify local media file." << endl;
    cout << "0. Back." << endl;
    cout << "Input your command: ";
}

void MediaFileInterface::modifyMenuInterface() {
    cout << "--------------------------------------------------------" << endl;
    cout << "MODIFY FILE OPTION:" << endl;
    cout << "1. Show metadata." << endl;
    cout << "2. Update metadata." << endl;
    cout << "3. Add to playlist." << endl;
    cout << "0. Back." << endl;
}

void MediaFileInterface::displayMediaFiles(MediaBrowser* browser, int page, int pageSize) {
    cout << "--------------------------------------------------------" << endl;
    int startIdx = (page - 1) * pageSize;
    int endIdx = min(startIdx + pageSize, static_cast<int>(browser->getMediaFiles().size()));

    for (int i = startIdx; i < endIdx; ++i) {
        cout << i+1 << ". " << browser->getMediaFiles()[i]->getName() << " - " << browser->getMediaFiles()[i]->getPath() << endl;
    }

    if(endIdx < (int)browser->getMediaFiles().size()) {
        string cont;
        cout << "Show more? (Y/N): ";
        getline(cin, cont);
        if(cont == "Y" || cont == "y") {
            displayMediaFiles(browser, page + 1, pageSize);
        }
    }
}

void MediaFileInterface::displayAudioFileMetadata(TagLib::Tag* tag, TagLib::FileRef fileRef) {
    cout << "1. Track:   " << tag->track() << endl;
    cout << "2. Album:   " << tag->album().toCString(true) << endl;
    cout << "3. Artist:  " << tag->artist().toCString(true) << endl;
    cout << "4. Publish Year:    " << tag->year() << endl;
    cout << "5. Genre:   " << tag->genre().toCString(true) << endl;
    cout << "6. Duration: " << fileRef.audioProperties()->length() << " seconds" << endl;
    cout << endl;
}

void MediaFileInterface::displayVideoFileMetadata(TagLib::Tag* tag, TagLib::FileRef fileRef, string file_path) {
    cout << "1. Video name:   " << tag->title().toCString(true) << endl;
    cout << "2. File Size: " << filesystem::file_size(file_path)/1000 << " Kbytes" << endl;
    cout << "3. Bit rate: " << fileRef.audioProperties()->bitrate() << " kbps" << endl;
    cout << "4. Duration: " << fileRef.audioProperties()->length() << " seconds" << endl;
    cout << endl;
}

void MediaFileInterface::enterMediaFileName(int input_case) {
    switch(input_case) {
        case ADD_TO_PLAYLIST:
            cout << "Enter index of media file that you want to add to this playlist: ";
            break;
        
        case DELETE_FROM_PLAYLIST:
            cout << "Enter index of media file that you want to delete from this playlist: ";
            break;

        default:
        cerr << "Error!" << endl;
    }   
}

void MediaFileInterface::duplicateFile() {
    cout << "This file has already been added in this playlist." << endl;
}

void MediaFileInterface::fileAddSuccess() {
    cout << "File added successfully!" << endl;
}

void MediaFileInterface::fileAddError() {
    cout << "File add failed. Media file name not found!" << endl;
}

void MediaFileInterface::fileDeleteSuccess(string file_name) {
    cout << "Media file with name '" << file_name << "' has been deleted from playlist." << endl;
}

void MediaFileInterface::fileDeleteError() {
    cout << "File deletion failed. Media file name not found!" << endl;
}

void MediaFileInterface::getMediaFileTypeError() {
    cerr << "Unknown media file type!" << endl;
}

void MediaFileInterface::listEmpty() {
    cout << "There is no media files to show." << endl;
}
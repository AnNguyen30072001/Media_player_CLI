#ifndef __MEDIA_FILE_INTERFACE_
#define __MEDIA_FILE_INTERFACE_

#include "main.h"

class MediaBrowser;

class MediaFileInterface
{
public:
    MediaFileInterface() = default;
    ~MediaFileInterface() = default;

    void menuInterface();

    void modifyMenuInterface();

    void displayMediaFiles(MediaBrowser *browser, int page, int pageSize);

    void displayAudioFiles(MediaBrowser *browser, int page, int pageSize);

    void displayAudioFileMetadata(TagLib::Tag *tag, TagLib::FileRef fileRef);

    void displayVideoFileMetadata(TagLib::Tag *tag, TagLib::FileRef fileRef, string file_path);

    void enterMediaFileName(int input_case);

    void duplicateFile();

    void fileAddSuccess();

    void fileAddError();

    void fileDeleteSuccess(string file_name);

    void fileDeleteError();

    void getMediaFileTypeError();

    void listEmpty();
};

#endif /* __MEDIA_FILE_INTERFACE_ */
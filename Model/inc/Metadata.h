#ifndef __METADATA_
#define __METADATA_

#include "main.h"
#include "MediaFileInterface.h"
#include "MetadataInterface.h"
#include "MainInterface.h"

class MediaBrowser;

class Metadata
{
private:
    string file_name;
    string file_path;
    int file_type;
    MediaFileInterface interface_media_file;
    MetadataInterface interface_metadata;
    MainInterface interface_main;

public:
    Metadata() = default;
    ~Metadata() = default;

    void viewMetadata(MediaBrowser *browser, int file_idx);

    void updateMetadata(MediaBrowser *browser, int file_idx);
};

#endif
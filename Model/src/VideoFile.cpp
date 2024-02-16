#include "main.h"
#include "VideoFile.h"

VideoFile::VideoFile(const string &n, const string &p) : MediaFile(n, p) {
    type = VIDEO_FILE_TYPE;
}
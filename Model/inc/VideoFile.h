#ifndef __VIDEO_FILE_
#define __VIDEO_FILE_

#include "main.h"

class VideoFile : public MediaFile {
private:

public:
    VideoFile(const string &n, const string &p);
    ~VideoFile() = default;
};

#endif /* __VIDEO_FILE_ */
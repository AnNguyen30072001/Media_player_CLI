#ifndef __AUDIO_FILE_
#define __AUDIO_FILE_

#include "main.h"

class AudioFile : public MediaFile {
private:

public:
    AudioFile(const string &n, const string &p);
    ~AudioFile() = default;
};

#endif /* __AUDIO_FILE_ */
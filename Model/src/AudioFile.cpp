#include "main.h"
#include "AudioFile.h"

AudioFile::AudioFile(const string &n, const string &p) : MediaFile(n, p) {
    type = AUDIO_FILE_TYPE;
}
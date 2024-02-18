#ifndef __MEDIA_PLAYER_INTERFACE_
#define __MEDIA_PLAYER_INTERFACE_

#include "main.h"

class MediaPlayerInterface
{
private:

public:
    MediaPlayerInterface() = default;
    ~MediaPlayerInterface() = default;

    void menuInterface();

    void loadFailed();

    void playFailed();

    void displayCurrentFileName(string);

    void displayCurrentTime(int, int, int, int);

    void notPlayingNotice();

    void enterPlayOption();

    void resumeMusic();

    void pauseMusic();

    void changeVolume();

    void endPlaylist();
};

#endif /* __MEDIA_PLAYER_INTERFACE_ */
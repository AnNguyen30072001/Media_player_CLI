#ifndef D7C31025_8304_468E_9946_7B906190DACD
#define D7C31025_8304_468E_9946_7B906190DACD

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

#include "MediaFile.h"
#include "Playlist.h"
#include "MediaFileInterface.h"
#include "PlaylistInterface.h"
#include "MainInterface.h"
#include "AudioFile.h"
#include "VideoFile.h"
#include "MediaBrowser.h"

enum {
    UNKNOWN_FILE_TYPE               = 0,
    AUDIO_FILE_TYPE                 = 1,
    VIDEO_FILE_TYPE                 = 2

};

enum {
    EXIT_APPLICATION                = 0,
    GO_TO_MEDIA_FILES               = 1,
    GO_TO_PLAYLISTS                 = 2
};

enum {
    BACK                            = 0,
    LIST_ALL_LOCAL_MEDIA_FILES      = 1,
    MODIFY_MEDIA_FILE               = 2
};

enum {
    VIEW_PLAYLIST                   = 1,
    CREATE_PLAYLIST                 = 2,
    DELETE_PLAYLIST                 = 3,
    ADD_TO_PLAYLIST                 = 4,
    DELETE_FROM_PLAYLIST            = 5,
    PLAYLIST_METADATA               = 6
};

enum {
    SHOW_METADATA                   = 1,
    UPDATE_METADATA                 = 2,
    ADD_LOCAL_TO_PLAYLIST           = 3
};

enum {
    MODIFY_TRACK                    = 1,
    MODIFY_ALBUM                    = 2,
    MODIFY_ARTIST                   = 3,
    MODIFY_YEAR                     = 4,
    MODIFY_GENRE                    = 5,
    MODIFY_AUDIO_DURATION           = 6
};

enum {
    MODIFY_VIDEO_NAME               = 1,
    MODIFY_SIZE                     = 2,
    MODIFY_BIT_RATE                 = 3,
    MODIFY_VIDEO_DURATION           = 4,
};

#endif /* D7C31025_8304_468E_9946_7B906190DACD */

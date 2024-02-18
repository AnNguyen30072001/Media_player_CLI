#include "MediaPlayer.h"

bool MediaPlayer::playing = false;
bool MediaPlayer::pause = false;
bool MediaPlayer::play_next = false;
bool MediaPlayer::play_back = false;
bool MediaPlayer::waiting_for_input = false;
bool MediaPlayer::force_stopped = false;

MediaPlayer::MediaPlayer()
{
    volume = MIX_MAX_VOLUME;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        SDL_Quit();
    }
}

MediaPlayer::~MediaPlayer()
{
    SDL_Quit();
    Mix_CloseAudio();
}

// int MediaPlayer::getAudioDuration(string filename)
// {
//     AVFormatContext* formatContext = avformat_alloc_context();
//     if (avformat_open_input(&formatContext, filename.c_str(), NULL, NULL) != 0) {
//         return -1; // Failed to open file
//     }

//     if (avformat_find_stream_info(formatContext, NULL) < 0) {
//         avformat_close_input(&formatContext);
//         return -1; // Failed to find stream info
//     }

//     int duration_seconds = formatContext->duration / AV_TIME_BASE;

//     avformat_close_input(&formatContext);

//     return duration_seconds;
// }

void MediaPlayer::playOption() 
{
    if(!playing) {
        interface_music_player.notPlayingNotice();
        return;
    }
    while (playing) {
        interface_music_player.enterPlayOption();
        char option;
        cin >> option;
        cin.ignore();
        waiting_for_input = true;

        switch (option) {
            case 'p':
                playOrPause();
                break;
            case 'n':
                next();
                break;
            case 'b':
                rewind();
                break;
            case 'v':
                changeVolume();
                break;
            case 's':
                playing = false;
                break;
            case 'e':
                return;
            default:
                interface_main.invalidChoiceInterface();
        }
    }
}

void MediaPlayer::playOrPause()
{
    if (Mix_PausedMusic()) {
        pause = false;
        Mix_ResumeMusic();
        interface_music_player.resumeMusic();
    } else {
        pause = true;
        Mix_PauseMusic();
        interface_music_player.pauseMusic();
    }
}

void MediaPlayer::next()
{
    // Mix_HaltMusic();
    play_next = true;
}

void MediaPlayer::rewind()
{
    play_back = true;
    // Mix_RewindMusic();
}

void MediaPlayer::changeVolume()
{
    int newVolume;
    interface_music_player.changeVolume();
    cin >> newVolume;
    if (newVolume >= 0 && newVolume <= 128) {
        volume = newVolume;
        Mix_VolumeMusic(volume);
    } else {
        interface_main.invalidChoiceInterface();
    }
}

void MediaPlayer::forceStopMusic()
{
    force_stopped = true;
}

bool MediaPlayer::isPlaying()
{
    return playing;
}

void MediaPlayer::resetForceStopFlag()
{
    force_stopped = false;
}
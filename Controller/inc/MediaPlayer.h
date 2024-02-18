#ifndef __MEDIA_PLAYER__
#define __MEDIA_PLAYER__

#include "main.h"
#include "MainInterface.h"
#include "MediaPlayerInterface.h"
#include "AudioFile.h"

class MediaPlayer
{
private:
    int volume;
    static bool playing;
    static bool pause;
    static bool play_next;
    static bool play_back;
    static bool waiting_for_input;
    static bool force_stopped;

    MainInterface interface_main;
    MediaPlayerInterface interface_music_player;

public:
    MediaPlayer();
    ~MediaPlayer();

    void playOption();

    void playOrPause();

    void next();

    void rewind();

    void changeVolume();

    void forceStopMusic();

    bool isPlaying();

    void resetForceStopFlag();

    static int getAudioDuration(string filename)
    {
        AVFormatContext *formatContext = avformat_alloc_context();
        if (avformat_open_input(&formatContext, filename.c_str(), NULL, NULL) != 0)
        {
            return -1; // Failed to open file
        }

        if (avformat_find_stream_info(formatContext, NULL) < 0)
        {
            avformat_close_input(&formatContext);
            return -1; // Failed to find stream info
        }

        int duration_seconds = formatContext->duration / AV_TIME_BASE;

        avformat_close_input(&formatContext);

        return duration_seconds;
    }

    static void playMusic(vector<AudioFile *> audioFiles, int file_idx)
    {
        MediaPlayerInterface interface_music_local;
        string file_path = audioFiles[file_idx]->getPath();
        int duration_seconds = getAudioDuration(file_path);

        interface_music_local.displayCurrentFileName(file_path);

        // Load music
        Mix_Music *music = Mix_LoadMUS(file_path.c_str());
        if (music == nullptr)
        {
            interface_music_local.loadFailed();
        }

        // Play the music
        if (Mix_PlayMusic(music, 1) == -1)
        {
            interface_music_local.playFailed();
            Mix_FreeMusic(music);
        }

        auto startTime = chrono::steady_clock::now();
        auto startPauseTime = chrono::steady_clock::now();
        auto now = chrono::steady_clock::now();
        int elapsedTime;
        int elapsedPauseTime = 0;
        int elapsedPauseTime_prev;
        bool pauseTimer = false;
        cout << endl;

        playing = true;
        while (playing)
        {
            if (waiting_for_input)
            {
                cout << endl;
                waiting_for_input = false;
            }

            if(pause)
            {
                if(!pauseTimer)
                {
                    startPauseTime = chrono::steady_clock::now();
                    pauseTimer = true;
                }
                    now = chrono::steady_clock::now();
                    elapsedPauseTime = chrono::duration_cast<chrono::seconds>(now - startPauseTime).count();
                    elapsedPauseTime += elapsedPauseTime_prev;
            }

            if (!pause)
            {
                pauseTimer = false;
                now = chrono::steady_clock::now();
                elapsedTime = chrono::duration_cast<chrono::seconds>(now - startTime).count();
                elapsedTime = elapsedTime - elapsedPauseTime;
                elapsedPauseTime_prev = elapsedPauseTime;
            }

            int currentMinutes = elapsedTime / 60;
            int currentSeconds = elapsedTime % 60;
            int durationMinutes = duration_seconds / 60;
            int durationSeconds = duration_seconds % 60;

            interface_music_local.displayCurrentTime(currentMinutes, currentSeconds, durationMinutes, durationSeconds);

            if (elapsedTime >= duration_seconds || play_next)
            {
                if ((file_idx + 1) < (int)audioFiles.size())
                {
                    play_next = false;
                    playMusic(audioFiles, file_idx + 1);
                }
                else
                {
                    interface_music_local.endPlaylist();
                    play_next = false;
                    playing = false;
                    return;
                }
            }

            if (force_stopped)
            {
                playing = false;
                return;
            }

            if (play_back)
            {
                play_back = false;
                startTime = now;
                elapsedTime = 0;
                Mix_RewindMusic();
            }

            // Delay to avoid high CPU usage
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        // Free resources
        Mix_FreeMusic(music);
    }
};

#endif /* __MEDIA_PLAYER__ */
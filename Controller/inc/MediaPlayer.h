#ifndef __MEDIA_PLAYER__
#define __MEDIA_PLAYER__

#include "main.h"
#include "MainInterface.h"
#include "MediaPlayerInterface.h"

class MediaPlayer
{
private:
    int volume;
    static bool playing;
    static bool pause;
    static bool waiting_for_input;
    static bool force_stopped;

    MainInterface interface_main;
    MediaPlayerInterface interface_music_player;
public:
    MediaPlayer();
    ~MediaPlayer();

    int getAudioDuration(string filename);

    void playOption();

    void playOrPause();

    void next();

    void rewind();

    void changeVolume();

    void forceStopMusic();

    bool isPlaying();

    void resetForceStopFlag();

    static void playMusic(string filename, int duration_seconds)
    {
        MediaPlayerInterface interface_music_local;
        // Load music
        Mix_Music *music = Mix_LoadMUS(filename.c_str());
        if (music == nullptr) {
            interface_music_local.loadFailed();
        }

        // Play the music
        if (Mix_PlayMusic(music, 1) == -1) {
            interface_music_local.playFailed();
            Mix_FreeMusic(music);
        }

        auto startTime = chrono::steady_clock::now();
        auto now = chrono::steady_clock::now();
        int elapsedTime;
        cout << endl;

        playing = true;
        while (playing) {
            if(waiting_for_input) {
                cout << endl;
                waiting_for_input = false;
            }

            if(!pause) {
                now = chrono::steady_clock::now();
                elapsedTime = chrono::duration_cast<chrono::seconds>(now - startTime).count();
            }
            
            int currentMinutes = elapsedTime / 60;
            int currentSeconds = elapsedTime % 60;
            int durationMinutes = duration_seconds / 60;
            int durationSeconds = duration_seconds % 60;
            
            interface_music_local.displayCurrentTime(currentMinutes, currentSeconds, durationMinutes, durationSeconds);

            if(elapsedTime >= duration_seconds || force_stopped == true)
            {
                playing = false;
                return;
            }

            // Delay to avoid high CPU usage
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        // Free resources
        Mix_FreeMusic(music);
    }
};


#endif /* __MEDIA_PLAYER__ */
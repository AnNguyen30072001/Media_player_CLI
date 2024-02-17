// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>
// #include <iostream>
// #include <string>
// #include <chrono>
// #include <thread>
// #include <atomic>

// extern "C" {
//     #include <libavformat/avformat.h>
// }

// using namespace std;

// // g++ temp.cpp -o temp -lSDL2 -lSDL2_mixer -pthread -I/usr/include/ffmpeg -lavformat

// std::atomic<bool> playing(true);
// std::atomic<bool> pause(false);
// std::atomic<bool> waiting_for_input(false);

// int getAudioDuration(const char* filename) {
//     av_register_all();

//     AVFormatContext* formatContext = avformat_alloc_context();
//     if (avformat_open_input(&formatContext, filename, NULL, NULL) != 0) {
//         return -1; // Failed to open file
//     }

//     if (avformat_find_stream_info(formatContext, NULL) < 0) {
//         avformat_close_input(&formatContext);
//         return -1; // Failed to find stream info
//     }

//     int durationInSeconds = formatContext->duration / AV_TIME_BASE;

//     avformat_close_input(&formatContext);

//     return durationInSeconds;
// }

// // Function to print current time and duration
// void printTime(int durationInSeconds) {
//     auto startTime = std::chrono::steady_clock::now();
//     auto now = std::chrono::steady_clock::now();
//     int elapsedTime;

//     cout << endl;

//     while (playing) {
//         if(waiting_for_input) {
//             cout << endl;
//             waiting_for_input = false;
//         }

//         if(!pause) {
//             now = std::chrono::steady_clock::now();
//             elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
//         }

//         // Move cursor to the beginning of the line
//         std::cout << "\r";

//         int currentMinutes = elapsedTime / 60;
//         int currentSeconds = elapsedTime % 60;
//         int durationMinutes = durationInSeconds / 60;
//         int durationSeconds = durationInSeconds % 60;

//         // Print the updated information
//         std::cout << "Current Time: " << currentMinutes << ":" << currentSeconds << " / " 
//                   << durationMinutes << ":" << durationSeconds << std::flush;

//         // Delay to avoid high CPU usage
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//     }
// }

// int main() {
//     // Initialize SDL
//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//         return -1;
//     }

//     // Initialize SDL_mixer
//     if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//         std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         SDL_Quit();
//         return -1;
//     }

//     // Load music
//     Mix_Music *music = Mix_LoadMUS("goofy.mp3");
//     if (music == nullptr) {
//         std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         Mix_CloseAudio();
//         SDL_Quit();
//         return -1;
//     }

//     // Play the music
//     if (Mix_PlayMusic(music, 1) == -1) {
//         std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
//         Mix_FreeMusic(music);
//         Mix_CloseAudio();
//         SDL_Quit();
//         return -1;
//     }

//     // Get music duration
//     int durationInSeconds = getAudioDuration("goofy.mp3");

//     // Start a separate thread to print time
//     std::thread timeThread(printTime, durationInSeconds);

//     // Join the time thread before exiting
//     timeThread.detach();

//     // Main thread handles user input
//     int volume = MIX_MAX_VOLUME; // Set initial volume
//     while (playing) {
//         std::cout << "Enter option: (p)lay/pause, (n)ext, (b)ack, (v)olume, (q)uit: ";
//         char option;
//         std::cin >> option;
//         waiting_for_input = true;

//         switch (option) {
//             case 'p':
//                 if (Mix_PausedMusic()) {
//                     pause = false;
//                     Mix_ResumeMusic();
//                     std::cout << "Resuming music..." << std::endl;
//                 } else {
//                     pause = true;
//                     Mix_PauseMusic();
//                     std::cout << "Pausing music..." << std::endl;
//                 }
//                 break;
//             case 'n':
//                 Mix_HaltMusic();
//                 playing = false;
//                 break;
//             case 'b':
//                 Mix_RewindMusic();
//                 break;
//             case 'v':
//                 int newVolume;
//                 std::cout << "Enter new volume (0-128): ";
//                 std::cin >> newVolume;
//                 if (newVolume >= 0 && newVolume <= 128) {
//                     volume = newVolume;
//                     Mix_VolumeMusic(volume);
//                 } else {
//                     std::cout << "Invalid volume level!" << std::endl;
//                 }
//                 break;
//             case 'q':
//                 playing = false;
//                 break;
//             default:
//                 std::cout << "Invalid option!" << std::endl;
//         }
//     }

//     // Free resources and quit SDL
//     Mix_FreeMusic(music);
//     Mix_CloseAudio();
//     SDL_Quit();

//     return 0;
// }

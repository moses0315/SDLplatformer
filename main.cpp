#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_AUDIO);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_Music* music = Mix_LoadMUS("example.mp3");
    if (music == NULL) {
        fprintf(stderr, "Failed to load MP3 file: %s\n", Mix_GetError());
        exit(1);
    }

    Mix_PlayMusic(music, 1);

    SDL_Delay(5000); // Wait for 5 seconds to play the entire MP3 file

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
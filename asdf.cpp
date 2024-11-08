#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL 초기화 실패: " << SDL_GetError() << std::endl;
        return 1;
    }

    // SDL_image 초기화
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image 초기화 실패: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // SDL_mixer 초기화
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer 초기화 실패: " << Mix_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // SDL_ttf 초기화
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf 초기화 실패: " << TTF_GetError() << std::endl;
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 창 생성
    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "창 생성 실패: " << SDL_GetError() << std::endl;
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "렌더러 생성 실패: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 이미지 로드
    SDL_Surface* imageSurface = IMG_Load("hello.png");
    if (!imageSurface) {
        std::cerr << "이미지 로드 실패: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    // 오디오 로드
    Mix_Music* music = Mix_LoadMUS("example.mp3");
    if (!music) {
        std::cerr << "오디오 로드 실패: " << Mix_GetError() << std::endl;
        SDL_DestroyTexture(imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    Mix_PlayMusic(music, -1);

    // 폰트 로드
    TTF_Font* font = TTF_OpenFont("PretendardVariable.ttf", 24);
    if (!font) {
        std::cerr << "폰트 로드 실패: " << TTF_GetError() << std::endl;
        Mix_FreeMusic(music);
        SDL_DestroyTexture(imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        Mix_CloseAudio();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // 텍스트 생성
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // 메인 루프
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // 화면 그리기
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        SDL_Rect textRect = {100, 100, 200, 50};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);
    }

    // 정리
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    Mix_FreeMusic(music);
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

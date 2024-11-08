#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine{
    public:
        static Engine* GetInstance(){
            return s_Instalce = (s_Instalce != nullptr)? s_Instalce : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool IsRunning(){return m_isRunning;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}

    private:
        Engine(){}
        bool m_isRunning;
        
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instalce;

};

#endif
#pragma once

#include <SDL.h>
#include <iostream>

class Window {
    public:
        Window(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
        ~Window();
        void UpdateWindow(void const* buffer, int pitch);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
};

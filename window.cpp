#include "window.h"
#include <SDL.h>
#include <iostream>
#include <unordered_map>

Window::Window(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    std::cout << "Window constructor" << std::endl;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}
Window::~Window() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Window destroyed" << std::endl;
}
void Window::UpdateWindow(void const* buffer, int pitch) {
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Window::ProcessInput(uint8_t* keys) {
    bool quit = false;
    SDL_Event event;

    static const std::unordered_map <SDL_Keycode, int> keyToIndex = {
        {SDLK_x, 0x0}, {SDLK_1, 0x1}, {SDLK_2, 0x2}, {SDLK_3, 0x3},
        {SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_a, 0x7},
        {SDLK_s, 0x8}, {SDLK_d, 0x9}, {SDLK_f, 0xA}, {SDLK_z, 0xB},
        {SDLK_4, 0xC}, {SDLK_r, 0xD}, {SDLK_c, 0xE}, {SDLK_v, 0xF},
    };

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            quit = true;
            break;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            auto it = keyToIndex.find(event.key.keysym.sym);
            if (it != keyToIndex.end()) {
                keys[it->second] = (event.type == SDL_KEYDOWN) ? 1 : 0;
            }
        }
    }
    return quit;
}

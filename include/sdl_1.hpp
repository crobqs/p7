#pragma once

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SDL_1 {
public:
    SDL_1() {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        font = TTF_OpenFont("./res/FiraCode.ttf", 40);
        if (!font) printf("Unable to load font\n");
        SDL_Surface* surface = TTF_RenderText_Shaded(font, text, fg, bg);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &fontRect.w, &fontRect.h);
        GAMELOOP: {
            while (SDL_PollEvent(&event)) {
                event_handling();
                if (quit) goto FORCE_TERMINATE;
            }
            update();
            SDL_Delay(FPS_DELAY);
        } goto GAMELOOP;

        FORCE_TERMINATE:
        clean();
    }

private:
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool quit = false;

    const int
    W = 900,
    H = 500,
    FPS_DELAY = 1000 / 60;

    TTF_Font* font;
    const char* text = "lmaoo";
    SDL_Color
    fg = {255, 0, 0, 255},
    bg = {255, 255, 0, 255};
    SDL_Texture* texture;
    SDL_Rect fontRect = {0};

    void event_handling() {
        switch (event.type) {
            case SDL_QUIT: {quit = true;} break;
            case SDL_KEYDOWN: {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: {quit = true;} break;
                }
            } break;
        }
    }

    void update() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &fontRect);
        SDL_RenderPresent(renderer);
    }

    void clean() {
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
};
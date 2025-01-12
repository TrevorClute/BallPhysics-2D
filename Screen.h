#pragma once
#include <chrono>
#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Ball.h"
#include "BallContainer.h"
#include <cstdint>


class Screen
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event e;
    std::chrono::system_clock::time_point lastPressedSpace;
    std::chrono::system_clock::time_point lastReset;
    std::chrono::system_clock::time_point lastFrame;
    BallContainer ballContainer;
    std::chrono::duration<double> duration;

public:
    Screen()
    {
        srand(time(0));
        lastPressedSpace = std::chrono::system_clock::now();
        lastReset = std::chrono::system_clock::now();
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("ilw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 700, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        helpers::keyboard = SDL_GetKeyboardState(nullptr);
    };

    void present()
    {
        std::chrono::system_clock::time_point currentFrame = std::chrono::system_clock::now();
        std::chrono::duration<double> deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        helpers::delta = deltaTime.count();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, 600, 1000, 600);
        ballContainer.present(renderer);
        SDL_RenderPresent(renderer);
    }

    void handleInput()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
        if (helpers::keyboard[SDL_SCANCODE_LEFT])
        {
            ballContainer.mainBallMoveLeft();
        }
        if (helpers::keyboard[SDL_SCANCODE_RIGHT])
        {
            ballContainer.mainBallMoveRight();
        }
        if (helpers::keyboard[SDL_SCANCODE_0])
        {
          std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
          duration = now - lastReset;
          if (duration.count() < 1) {
            return;
            }
            lastReset = now;
            ballContainer.reset();
        }
        if (helpers::keyboard[SDL_SCANCODE_SPACE])
        {
            // cooldown
            std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
            duration = now - lastPressedSpace;
            if (duration.count() < 1)
            {
                return;
            }
            lastPressedSpace = now;
            ballContainer.mainBallDrop();
        }
    }
};

#endif

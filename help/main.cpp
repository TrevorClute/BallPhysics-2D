#include <SDL2/SDL.h>
#include <vector>

class Dot
{
private:
    std::vector<SDL_FPoint> points;

public:
    Dot()
    {
        for (int i = 0; i < 10; i++)
        {
            SDL_FPoint point;
            point.x = i;
            point.y = 0;
            points.push_back(point);
        }
    }
    void present(SDL_Renderer *renderer)
    {
        moveRight();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPointsF(renderer, points.data(), points.size());
    }
    void moveRight()
    {
        for (int i = 0; i < 10; i++)
        {
            points[i].x += 1;
            points[i].y += 1;
        }
    }
};

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("test", 0, 0, 800, 800, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;
    Dot dot;

    while (true)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        dot.present(renderer);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }
    return 0;
}
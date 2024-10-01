#include <SDL2/SDL.h>
#include "Screen.h"
#include <cstdlib>

int main()
{
    Screen screen;
    while (true)
    {
        screen.present();
        screen.handleInput();
    }
    return 0;
}
#include <SDL2/SDL.h>
#include "Screen.h"

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

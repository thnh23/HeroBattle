#include "Timer.h"
#include "SDL.h"

Timer*  Timer::m_Instance = nullptr;


float Timer::getTime()
{
    return SDL_GetTicks()/(1000.0f);
}



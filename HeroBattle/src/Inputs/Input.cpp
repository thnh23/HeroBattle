#include "Input.h"
#include"Engine.h"

Input* Input::m_Instance = nullptr;
Input::Input(){
    m_KeyStates =SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYDOWN:
                m_KeyStates =SDL_GetKeyboardState(nullptr);
                break;
            case SDL_KEYUP:
               m_KeyStates =SDL_GetKeyboardState(nullptr);
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return m_KeyStates[key] == 1;
}





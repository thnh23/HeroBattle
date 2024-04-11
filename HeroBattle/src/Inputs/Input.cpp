#include "Input.h"
#include"Engine.h"

Input* Input::m_Instance = nullptr;
Input::Input(){
    m_KeyStates =SDL_GetKeyboardState(nullptr);
}
void Input::init()
{
     for (int i = 0; i < 3; i++)
     {
          mouseButtonStates.push_back(false);
     }
     mPos = new Vector2D(0, 0);
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
                m_KeyStates = SDL_GetKeyboardState(nullptr);
                break;
            case SDL_KEYUP:
               m_KeyStates = SDL_GetKeyboardState(nullptr);
                break;
            case SDL_MOUSEMOTION:
              onMouseMove(event);
                break;
           case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;

         case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;

        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return (m_KeyStates[key] == 1);
}

void Input::onMouseButtonDown(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;
	}
        else if (e.button.button = SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;
	}
        else if (e.button.button = SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;
	}
	   Engine::GetInstance()->getStateMachine()->onMouseButtonDown(e);
}

void Input::onMouseButtonUp(SDL_Event& e)
{
	if (e.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
	}
        else if (e.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
	}
        else if (e.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
	}
	Engine::GetInstance()->getStateMachine()->onMouseButtonUp(e);
}

void Input::onMouseMove(SDL_Event& e)
{
	mPos->setX(e.motion.x);
	mPos->setY(e.motion.y);
	Engine::GetInstance()->getStateMachine()->onMouseMove(e);
}

void Input::reset()
{
     for (int i = 0; i < mouseButtonStates.size(); i++)
     {
          mouseButtonStates[i] = false;
     }
}

 bool Input::getMouseButtonState(int buttonNum)
 {
     return  mouseButtonStates[buttonNum];
 }





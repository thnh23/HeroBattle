#ifndef INPUT_H
#define INPUT_H
#include"SDL.h"
#include "Vector2D.h"
#include<vector>
#include<iostream>

enum mouse_buttons
{
     LEFT = 0,
     MIDDLE = 1,
     RIGHT = 2
};
class Input
{
  public:
     static Input* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new Input();
  }
  void init();
  void Listen();
  bool GetKeyDown(SDL_Scancode key);
  bool getMouseButtonState(int buttonNum);
Vector2D* getMousePos()
{
     return mPos;
}

void reset();


  private:
     Input();
      static Input* m_Instance;

      //keyboard
     const Uint8* m_KeyStates;
    // mouse
    std::vector<bool> mouseButtonStates;

Vector2D* mPos;

void onMouseMove(SDL_Event& e);
void onMouseButtonDown(SDL_Event& e);
void onMouseButtonUp(SDL_Event& e);

};

#endif

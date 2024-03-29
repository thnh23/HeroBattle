#ifndef INPUT_H
#define INPUT_H
#include"SDL.h"

class Input
{
  public:
     static Input* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new Input();
  }
  void Listen();
  bool GetKeyDown(SDL_Scancode key);
  private:
     Input();
     const Uint8* m_KeyStates;
     static Input* m_Instance;
};

#endif

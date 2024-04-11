
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include"SDL.h"
class GameState
{
  public:
       virtual void update(float dt) = 0;
       virtual void render() = 0;
       virtual bool onEnter() = 0;
       virtual bool onExit() = 0;
       virtual void onMouseButtonUp(SDL_Event& e) = 0;
        virtual void onMouseButtonDown(SDL_Event& e) = 0;
        virtual void onMouseMove(SDL_Event& e) = 0;
       virtual std::string getStateID() const = 0;

};
#endif // GAMESTATE_H

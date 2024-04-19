#pragma once
#ifndef MENUSTATE_H
#define MENUSTATE_H
#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>

class MenuState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return menuID; }

    private:
        static const std::string menuID;
       std::vector<Button*> menuButton;
};

#endif // MENUSTATE_H

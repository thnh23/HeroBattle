#pragma once
#ifndef SHOPSTATE_H
#define SHOPSTATE_H
#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>


class ShopState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return shopID; }

    private:
        static const std::string shopID;
       std::vector<Button*> shopButton;

};

#endif // SHOPSTATE_H

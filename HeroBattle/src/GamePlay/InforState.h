#pragma once
#ifndef INFORSTATE_H
#define INFORSTATE_H
#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>

class InforState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return inforID; }

    private:
        static const std::string inforID;
       Button* closeInfor;
};

#endif // INFORSTATE_H

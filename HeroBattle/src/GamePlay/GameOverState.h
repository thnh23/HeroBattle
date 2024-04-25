#pragma once
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H


#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>
#include"SDL_mixer.h"

class GameOverState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return gameOverID; }

    private:
        static const std::string gameOverID;
       std::vector<Button*> gameOverButton;
       Mix_Chunk* m_LoseMusic;
};


#endif // GAMEOVERSTATE_H

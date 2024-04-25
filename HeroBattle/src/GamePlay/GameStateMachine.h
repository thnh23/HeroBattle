
#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include"GameState.h"
#include<vector>
#include"SDL.h"

class GameStateMachine
{
    public:
        GameStateMachine() {}
        virtual ~GameStateMachine() {}

        void pushState(GameState* state)
        {
       gameStates.push_back(state);
       gameStates.back()->onEnter();
        }

       void changeState(GameState* state)
       {
           if (!gameStates.empty())
       {
              if (gameStates.back()->getStateID() == state->getStateID())
              {
                     return;
              }

       gameStates.push_back(state);

       if (!gameStates.empty())
       {
              if (gameStates.back()->onExit())
              {
                gameStates.erase(gameStates.end() - 2);
              }
       }

       gameStates.back()->onEnter();
       }
       }
       void popState()
       {
            if (!gameStates.empty())
       {
              if (gameStates.back()->onExit())
              {
                     gameStates.erase(gameStates.end() - 1);
              }
       }
       }

       void update(float dt)
       {
       if (!gameStates.empty())
       {
              gameStates.back()->update( dt);
       }
       }
       void render()
       {
            if (!gameStates.empty())
       {
              gameStates.back()->render();
       }
       }

        void onMouseButtonUp(SDL_Event& e)
        {
             if (!gameStates.empty())
       {
              gameStates.back()->onMouseButtonUp(e);
       }
        }
       void onMouseButtonDown(SDL_Event& e)
       {
             if (!gameStates.empty())
       {
              gameStates.back()->onMouseButtonDown(e);
       }
       }
       void onMouseMove(SDL_Event& e)
       {
            if (!gameStates.empty())
       {
              gameStates.back()->onMouseMove(e);
       }
       }
    private:
         std::vector<GameState*> gameStates;
};

#endif // GAMESTATEMACHINE_H

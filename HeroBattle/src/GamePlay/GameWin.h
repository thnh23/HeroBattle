#ifndef GAMEWIN_H
#define GAMEWIN_H


#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>
#include"SDL_mixer.h"
class GameWin : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return gameWinID; }

    private:
        static const std::string gameWinID;
       std::vector<Button*> gameWinButton;
       Mix_Chunk* m_WinMusic;
};
#endif // GAMEWIN_H

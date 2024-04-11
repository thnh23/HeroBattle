#ifndef PLAYSTATE_H
#define PLAYSTATE_H


#include "GameState.h"
#include <string>
#include<vector>
#include"Button.h"

class PlayState : public GameState
{
public:

       virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return playID; }

private:

       static const std::string playID;
        std::vector<Button*> playButton;

};

#endif // PLAYSTATE_H

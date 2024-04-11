#ifndef RESUMESTATE_H
#define RESUMESTATE_H


#include"GameState.h"
#include<string>
#include"Button.h"
#include<vector>

class ResumeState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e);
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return resumeID; }

    private:
        static const std::string resumeID;
       std::vector<Button*> resumeButton;
};

#endif // RESUMESTATE_H

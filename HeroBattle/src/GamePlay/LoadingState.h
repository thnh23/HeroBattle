 #ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#include"GameState.h"
#include<string>
#include"Animation.h"
class LoadingState : public GameState
{
    public:
      virtual void update(float dt);
       virtual void render();

       virtual bool onEnter();
       virtual bool onExit();

       virtual void onMouseButtonDown(SDL_Event& e){};
       virtual void onMouseButtonUp(SDL_Event& e){};
       virtual void onMouseMove(SDL_Event& e){};

       virtual std::string getStateID() const { return loadingID; }

    private:
        static const std::string loadingID;
         float timePresent;
         Animation* loadingAnimation;
};


#endif // LOADINGSTATE_H

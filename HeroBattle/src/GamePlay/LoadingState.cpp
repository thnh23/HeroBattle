
#include "LoadingState.h"
#include"Engine.h"
#include"TextureManager.h"
#include"PlayState.h"

const std::string LoadingState::loadingID = "LOADING";
void LoadingState::update(float dt)
{
    loadingAnimation->Update();
   timePresent-=dt;
   if(timePresent<=0)  Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
}

void LoadingState::render()
{
 TextureManager::GetInstance()->Draw("black_img",0,0,1920,1080);
 TextureManager::GetInstance()->RenderText("LOADING...",{255,255,255},SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-50,50);
 loadingAnimation->DrawNoCamera(SCREEN_WIDTH/2-10,SCREEN_HEIGHT/2,48,48);
}

bool LoadingState::onEnter()
{
    loadingAnimation= new Animation();
    loadingAnimation->setProps("loading",1,12,120);
    timePresent= 2;
    return true;
}

bool LoadingState::onExit()
{
    return true;
}

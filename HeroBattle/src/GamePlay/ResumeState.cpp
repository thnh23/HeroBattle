#include "ResumeState.h"
#include "Button.h"
#include"Engine.h"
#include"GamePlay.h"
#include"HUD.h"
#include"GameStateMachine.h"
#include"PlayState.h"
#include"MenuState.h"
#include"LoadingState.h"


const std::string ResumeState::resumeID = "RESUME";
void ResumeState::update(float dt)
{
 for(auto it = resumeButton.begin(); it!= resumeButton.end();it++)
 {
    (*it)->update();
 }
}

void ResumeState::render()
{
  TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  GamePlay::GetInstance()->draw();
  TextureManager::GetInstance()->Draw("black_img",0,0,1920,1080);
  TextureManager::GetInstance()->DrawAlphaMode("black_img",100);
  TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-150,200,300,1,0);
    for(auto it = resumeButton.begin(); it!= resumeButton.end();it++)
 {
    (*it)->draw();
 }
}

bool ResumeState::onEnter()
{
    HUD::GetInstance()->getTimer()->pause();
    Input::GetInstance()->reset();
  resumeButton.push_back(new Button("continuebutton",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2-90,64,60,1));
  resumeButton.push_back(new Button("homebutton",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2-20,64,60,1));
  resumeButton.push_back(new Button("restartbutton",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2+50,63,60,1));
  return true;
}

bool ResumeState::onExit()
{
     for(auto it = resumeButton.begin(); it != resumeButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         resumeButton.erase(it);
         --it;
    }
  return true;
}

void ResumeState::onMouseButtonUp(SDL_Event& e)
{
  if(resumeButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
         HUD::GetInstance()->getTimer()->unpause();
        Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }
    if(resumeButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
    HUD::GetInstance()->initHUD();
    GamePlay::GetInstance()->init();
    Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
    Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
    }
    if(resumeButton[2]->checkCollision(Input::GetInstance()->getMousePos()))
    {
    HUD::GetInstance()->initHUD();
    GamePlay::GetInstance()->init();
    Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
     Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
    }
}

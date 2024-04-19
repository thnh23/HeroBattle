#include "PlayState.h"
#include <iostream>
#include "Engine.h"
#include "GameStateMachine.h"
#include "Button.h"
#include"Camera.h"
#include"HUD.h"
#include"GamePlay.h"
#include"ResumeState.h"
#include"ShopState.h"
#include"GameOverState.h"

const std::string PlayState::playID = "PLAY";

void PlayState::update(float dt)
{
 Engine::GetInstance()->GetMap()->Update();
 Camera::GetInstance()->Update();
  HUD::GetInstance()->updateHUD();
   GamePlay::GetInstance()->update(dt);
   for(auto it = playButton.begin(); it!= playButton.end();it++)
{
    (*it)->update();
}
}


void PlayState::render()
{
 TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  HUD::GetInstance()->drawHUD();
   GamePlay::GetInstance()->draw();
    for(auto it = playButton.begin(); it!= playButton.end();it++)
{
    (*it)->draw();
}
   if(GamePlay::GetInstance()->getKnight()->getHealth()<=0)   Engine::GetInstance()->getStateMachine()->changeState(new GameOverState());
}

bool PlayState::onEnter()
{
    Input::GetInstance()->reset();
    playButton.push_back( new Button("shopbutton",SCREEN_WIDTH-150,5,64,60,1));
    playButton.push_back( new Button("settingbutton",SCREEN_WIDTH-70,5,63,60,1));
    std::cout << "entering PlayState..." << std::endl;
    return true;
}

bool PlayState::onExit()
{
     for(auto it = playButton.begin(); it != playButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         playButton.erase(it);
         --it;
    }
        std::cout << "exiting PlayState..." << std::endl;
        return true;
}


void PlayState::onMouseButtonUp(SDL_Event& e)
{
  if(playButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
         Engine::GetInstance()->getStateMachine()->changeState(new ShopState());
    }
    if(playButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
       Engine::GetInstance()->getStateMachine()->changeState(new ResumeState());
    }
}


#include "PlayState.h"
#include <iostream>
#include "Engine.h"
#include "GameStateMachine.h"
#include "Button.h"
#include"Camera.h"
#include"HUD.h"
#include"GamePlay.h"
#include"ResumeState.h"

const std::string PlayState::playID = "PLAY";

void PlayState::update(float dt)
{
 Engine::GetInstance()->GetMap()->Update();
 Camera::GetInstance()->Update();
 GamePlay::GetInstance()->update(dt);
  HUD::GetInstance()->updateHUD();
}


void PlayState::render()
{
 TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  GamePlay::GetInstance()->draw();
  HUD::GetInstance()->drawHUD();
    for(auto it = playButton.begin(); it!= playButton.end();it++)
{
    (*it)->draw();
}
}

bool PlayState::onEnter()
{
    playButton.push_back( new Button("shopbutton",SCREEN_WIDTH-150,5,64,60,1));
    playButton.push_back( new Button("settingbutton",SCREEN_WIDTH-70,5,63,60,1));
    std::cout << "entering PlayState..." << std::endl;
    return true;
}

bool PlayState::onExit()
{
        std::cout << "exiting PlayState..." << std::endl;
        return true;
}


void PlayState::onMouseButtonUp(SDL_Event& e)
{
  if(playButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {

    }
    if(playButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
       Engine::GetInstance()->getStateMachine()->changeState(new ResumeState());
    }
}


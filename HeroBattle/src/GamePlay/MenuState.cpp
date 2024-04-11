#include "MenuState.h"
#include <iostream>
#include "Engine.h"
#include "GameStateMachine.h"
#include"Button.h"
#include"PlayState.h"
#include"GamePlay.h"
#include"HUD.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update(float dt)
{

}

void MenuState::render()
{
     SDL_Color color{10,200,45};
    TextureManager::GetInstance()->DrawFrameNoCamera("menu_bg",-100,0,1138,640,1,0);
     TextureManager::GetInstance()->RenderText("HERO BATTLE",color,SCREEN_WIDTH/2-180,SCREEN_HEIGHT/2-100,100);
   for(auto it = menuButton.begin(); it!= menuButton.end();it++)
{
    (*it)->draw();
}
}

bool MenuState::onEnter()
{
    menuButton.push_back ( new Button("playbutton",SCREEN_WIDTH/2-74,SCREEN_HEIGHT/2,127,60,1));
    menuButton.push_back(  new Button("inforbutton",SCREEN_WIDTH/2-74,SCREEN_HEIGHT/2+85,127,60,1));
    menuButton.push_back( new Button("closebutton",SCREEN_WIDTH/2-74,SCREEN_HEIGHT/2+170,127,60,1));
    return true;
}

bool MenuState::onExit()
{
     for(auto it = menuButton.begin(); it != menuButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         menuButton.erase(it);
         --it;
    }
       std::cout << "exiting MenuState..." << std::endl;
       return true;
}



void MenuState::onMouseButtonUp(SDL_Event& e)
{
    if(menuButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }
    if(menuButton[2]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        Engine::GetInstance()->Quit();
    }
}


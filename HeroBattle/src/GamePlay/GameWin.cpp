#include "GameWin.h"
#include<string>
#include"Engine.h"
#include"Button.h"
#include"GameStateMachine.h"
#include"PlayState.h"
#include"MenuState.h"
#include"HUD.h"
#include"GamePlay.h"
const std::string GameWin::gameWinID = "GAMEWIN";
void GameWin::update(float dt)
{
for(auto it = gameWinButton.begin(); it!= gameWinButton.end();it++)
 {
    (*it)->update();
 }

}

void GameWin::render()
{
    TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  GamePlay::GetInstance()->draw();
 TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-200,600,400,1,0);
 TextureManager::GetInstance()->RenderText("YOU WIN",{255,255,255},SCREEN_WIDTH/2-120,SCREEN_HEIGHT/2-100,100);
 for(auto it = gameWinButton.begin(); it!= gameWinButton.end();it++)
 {
    (*it)->draw();
 }

}

bool GameWin::onEnter()
{
    gameWinButton.push_back(new Button("homebutton",SCREEN_WIDTH/2-80,SCREEN_HEIGHT/2+50,64,60,1));
    gameWinButton.push_back(new Button("restartbutton",SCREEN_WIDTH/2+30,SCREEN_HEIGHT/2+50,63,60,1));
return true;
}

bool GameWin::onExit()
{
      for(auto it = gameWinButton.begin(); it != gameWinButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         gameWinButton.erase(it);
         --it;
    }
return true;
}

void GameWin::onMouseButtonUp(SDL_Event& e)
{
if(gameWinButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        HUD::GetInstance()->initHUD();
        GamePlay::GetInstance()->init();
        Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
        Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
    }
    if(gameWinButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        HUD::GetInstance()->initHUD();
        GamePlay::GetInstance()->init();
        Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
         Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }
}

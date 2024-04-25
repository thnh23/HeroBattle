#include "GameOverState.h"
#include<string>
#include"Engine.h"
#include"Button.h"
#include"GameStateMachine.h"
#include"PlayState.h"
#include"MenuState.h"
#include"HUD.h"
#include"GamePlay.h"
const std::string GameOverState::gameOverID = "GAMEOVER";
void GameOverState::update(float dt)
{
for(auto it = gameOverButton.begin(); it!= gameOverButton.end();it++)
 {
    (*it)->update();
 }
 GamePlay::GetInstance()->getKnight()->isDied=true;
 GamePlay::GetInstance()->getKnight()->AnimationState();
}

void GameOverState::render()
{
    TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  GamePlay::GetInstance()->draw();
 TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-200,600,400,1,0);
 TextureManager::GetInstance()->RenderText("GAME OVER",{255,255,255},SCREEN_WIDTH/2-155,SCREEN_HEIGHT/2-100,100);
 for(auto it = gameOverButton.begin(); it!= gameOverButton.end();it++)
 {
    (*it)->draw();
 }

}

bool GameOverState::onEnter()
{
    gameOverButton.push_back(new Button("homebutton",SCREEN_WIDTH/2-80,SCREEN_HEIGHT/2+50,64,60,1));
    gameOverButton.push_back(new Button("restartbutton",SCREEN_WIDTH/2+30,SCREEN_HEIGHT/2+50,63,60,1));
    m_LoseMusic = Mix_LoadWAV("Maps/kl-peach-game-over-iii-142453.mp3");
    if(m_LoseMusic ==nullptr){ std::cout<<"nhot"<<std::endl;}
    Mix_VolumeChunk(m_LoseMusic,40);
    Mix_PlayChannel(1,m_LoseMusic,0);
    return true;
}

bool GameOverState::onExit()
{
      for(auto it = gameOverButton.begin(); it != gameOverButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         gameOverButton.erase(it);
         --it;
    }
    Mix_FreeChunk(m_LoseMusic);
return true;
}

void GameOverState::onMouseButtonUp(SDL_Event& e)
{
if(gameOverButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        HUD::GetInstance()->initHUD();
        GamePlay::GetInstance()->init();
        Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
        Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
    }
    if(gameOverButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        HUD::GetInstance()->initHUD();
        GamePlay::GetInstance()->init();
        Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
         Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }
}

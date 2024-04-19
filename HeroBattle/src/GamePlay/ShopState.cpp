#include "ShopState.h"
#include "Engine.h"
#include "GamePlay.h"
#include"HUD.h"
#include"GameStateMachine.h"
#include"Button.h"
#include"PlayState.h"
#include"GameOverState.h"
const std::string ShopState::shopID = "SHOP";
void ShopState::update(float dt)
{
  GamePlay::GetInstance()->update(dt);
  HUD::GetInstance()->updateHUD();
   for(auto it = shopButton.begin(); it!= shopButton.end();it++)
 {
    (*it)->update();
 }
}

void ShopState::render()
{
  TextureManager::GetInstance()->Draw("bg",0,0,1920,1080);
  Engine::GetInstance()->GetMap()->Render();
  GamePlay::GetInstance()->draw();
  TextureManager::GetInstance()->Draw("black_img",0,0,1920,1080);
  TextureManager::GetInstance()->DrawAlphaMode("black_img",100);
  HUD::GetInstance()->drawHUD();
  TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-200,600,400,1,0);
  TextureManager::GetInstance()->DrawFrameNoCamera("red_poison",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2-80,32,32,1,0);
  TextureManager::GetInstance()->DrawFrameNoCamera("sword",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2+20,32,32,1,0);
  TextureManager::GetInstance()->DrawFrameNoCamera("shield",SCREEN_WIDTH/2-30,SCREEN_HEIGHT/2+120,32,32,1,0);

  TextureManager::GetInstance()->RenderText("SHOP",{255,255,255},SCREEN_WIDTH/2+120,SCREEN_HEIGHT/2-170,70);

  TextureManager::GetInstance()->RenderText("+20 health",{255,255,255},SCREEN_WIDTH/2+30,SCREEN_HEIGHT/2-90,50);
  TextureManager::GetInstance()->RenderText("+3 attack",{255,255,255},SCREEN_WIDTH/2+30,SCREEN_HEIGHT/2+10,50);
  TextureManager::GetInstance()->RenderText("+3 deffend",{255,255,255},SCREEN_WIDTH/2+30,SCREEN_HEIGHT/2+110,50);

  TextureManager::GetInstance()->RenderText("30 coin",{255,255,255},SCREEN_WIDTH/2+300,SCREEN_HEIGHT/2-90,50);
  TextureManager::GetInstance()->RenderText("50 coin",{255,255,255},SCREEN_WIDTH/2+300,SCREEN_HEIGHT/2+10,50);
  TextureManager::GetInstance()->RenderText("50 coin",{255,255,255},SCREEN_WIDTH/2+300,SCREEN_HEIGHT/2+110,50);

  TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",0,SCREEN_HEIGHT/2-200,300,400,1,0);
  TextureManager::GetInstance()->RenderText("STATS",{255,255,255},80,SCREEN_HEIGHT/2-170,70);
  TextureManager::GetInstance()->RenderText("HEALTH: " + std::to_string(GamePlay::GetInstance()->getKnight()->getHealth()) +"/" + std::to_string(MAX_HEALTH),{255,255,255},40,SCREEN_HEIGHT/2-90,50);
  TextureManager::GetInstance()->RenderText("ATTACK: " + std::to_string(GamePlay::GetInstance()->getKnight()->getAttack()),{255,255,255},40,SCREEN_HEIGHT/2,50);
    TextureManager::GetInstance()->RenderText("DEFFEND: " + std::to_string(GamePlay::GetInstance()->getKnight()->getDeffend()),{255,255,255},40,SCREEN_HEIGHT/2+90,50);
    for(auto it = shopButton.begin(); it!= shopButton.end();it++)
 {
    (*it)->draw();
 }
  if(GamePlay::GetInstance()->getKnight()->getHealth()<=0)   Engine::GetInstance()->getStateMachine()->changeState(new GameOverState());
}

bool ShopState::onEnter()
{
    Input::GetInstance()->reset();
   shopButton.push_back( new Button("buy",SCREEN_WIDTH/2+200,SCREEN_HEIGHT/2-80,64,32,1));
   shopButton.push_back( new Button("buy",SCREEN_WIDTH/2+200,SCREEN_HEIGHT/2+20,64,32,1));
   shopButton.push_back( new Button("buy",SCREEN_WIDTH/2+200,SCREEN_HEIGHT/2+120,64,32,1));
    shopButton.push_back( new Button("back",SCREEN_WIDTH-100,20,64,32,1));
  return true;
}

bool ShopState::onExit()
{

 for(auto it = shopButton.begin(); it != shopButton.end(); ++it)
    {
         delete (*it);
         (*it) = nullptr;
         shopButton.erase(it);
         --it;
    }
  return true;
}

void ShopState::onMouseButtonUp(SDL_Event& e)
{
 if(shopButton[0]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        if((GamePlay::GetInstance()->getNumCoin()>=30) &&  (GamePlay::GetInstance()->getKnight()->getHealth() != MAX_HEALTH))
        {
         GamePlay::GetInstance()->updateCoin(30);
         GamePlay::GetInstance()->getKnight()->updateHealth(-30);
        }
    }
    if(shopButton[1]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        if((GamePlay::GetInstance()->getNumCoin()>=50))
        {
       GamePlay::GetInstance()->updateCoin(50);
        GamePlay::GetInstance()->getKnight()->updateAttack(3);
        }
    }
    if(shopButton[2]->checkCollision(Input::GetInstance()->getMousePos()))
    {
        if(GamePlay::GetInstance()->getNumCoin()>=50)
        {
         GamePlay::GetInstance()->updateCoin(50);
         GamePlay::GetInstance()->getKnight()->updateDeffend(3);
        }
    }
    if(shopButton[3]->checkCollision(Input::GetInstance()->getMousePos()))
    {
          Engine::GetInstance()->getStateMachine()->changeState(new PlayState());
    }
}

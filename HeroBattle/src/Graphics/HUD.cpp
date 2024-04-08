#include "HUD.h"
#include "GamePlay.h"
#include<stdio.h>
#include"SDL.h"
#include"SDL_image.h"
#include"Engine.h"

HUD* HUD::m_Instance=nullptr;
void HUD::initHUD()
{
    health=GamePlay::GetInstance()->getKnight()->getHealth();
    coin=GamePlay::GetInstance()->getNumCoin();
}

void HUD::updateHUD()
{
  if(health<0) health=0;
   coin=GamePlay::GetInstance()->getNumCoin();
}


void HUD::drawHUD()
{
    //create health bar
SDL_Surface* healthbar_sur = IMG_Load("Image/Bar.png");
SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), healthbar_sur);
SDL_Rect rect{85, 5, MAX_HEALTH, 22};
health=GamePlay::GetInstance()->getKnight()->getHealth();
SDL_Rect rect2{87, 7, health, 18};
SDL_RenderCopy(Engine::GetInstance()->getRenderer(), healthbar_tex, NULL, &rect);
SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 255, 0, 0, 255);
SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), &rect2);
SDL_Color color{255,255,255};
TextureManager::GetInstance()->RenderText("HEALTH:",color,2,0,35);

TextureManager::GetInstance()->RenderText("COIN: " + std::to_string(coin),color,2,40,35);
}


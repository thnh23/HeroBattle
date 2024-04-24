#include "HUD.h"
#include "GamePlay.h"
#include<stdio.h>
#include"SDL.h"
#include"SDL_image.h"
#include"Engine.h"
#include"Timer.h"

HUD* HUD::m_Instance=nullptr;
void HUD::initHUD()
{
    health=100;
    GamePlay::GetInstance()->setNumCoin(1000);
    m_Timer.start();
    minute=0;
    second=0;
    energy=0;
}

void HUD::updateHUD()
{
    if(minute==0) second=m_Timer.getTicks()/1000;
    else second=m_Timer.getTicks()/1000 - 60*minute;
    if(second/60 != 0)
    {
        minute++;
    }
    if(second<10 && minute<10) time="0"+std::to_string(minute)+":0"+std::to_string(second);
    else if(minute<10) time="0"+std::to_string(minute)+":"+std::to_string(second);
    else if(second<10) time=std::to_string(minute)+":0"+std::to_string(second);
   health =GamePlay::GetInstance()->getKnight()->getHealth();
   coin=GamePlay::GetInstance()->getNumCoin();
   energy = GamePlay::GetInstance()->getKnight()->getEnergy();
}


void HUD::drawHUD()
{
    //create energy bar
SDL_Surface* healthbar_sur = IMG_Load("Image/Bar.png");
SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), healthbar_sur);
SDL_FreeSurface(healthbar_sur);
SDL_Rect rect3{85,40,100+3,22};
SDL_Rect rect4{87,42,energy,18};
SDL_RenderCopy(Engine::GetInstance()->getRenderer(), healthbar_tex, NULL, &rect3);
SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(),0,0,255,0);
SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), &rect4);

//health bar
SDL_Rect rect{85, 5, MAX_HEALTH+3, 22};
SDL_Rect rect2{87, 7, health, 18};
SDL_RenderCopy(Engine::GetInstance()->getRenderer(), healthbar_tex, NULL, &rect);
SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(),255,0,0,0);
SDL_RenderFillRect(Engine::GetInstance()->getRenderer(), &rect2);
SDL_DestroyTexture(healthbar_tex);

//text
SDL_Color color{255,255,255};
TextureManager::GetInstance()->RenderText("HEALTH:",color,2,0,35);

TextureManager::GetInstance()->RenderText("COIN: " + std::to_string(coin),color,2,65,35);

TextureManager::GetInstance()->RenderText("ENERGY: ",color,2,36,35);

TextureManager::GetInstance()->RenderText(time,color,SCREEN_WIDTH/2,0,50);


}


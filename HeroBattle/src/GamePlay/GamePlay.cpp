#include "GamePlay.h"
#include "Engine.h"
#include"Collision.h"
#include <iostream>
#include"GameObject.h"
#include"TextureManager.h"
#include"Input.h"


GamePlay* GamePlay::m_Instance = nullptr;

void GamePlay::init()
{
  player = new Knight(new Properties("knight",1500,0,72,86));
   for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
    }
   for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
  }

}

void GamePlay::update(float dt)
{
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
    if(player->m_CoolDown==0) (*it)->isHitting = false;
    if((*it)->isAttacking)  enemyAttack.push_back(*it);
    }

     for(auto it = enemyAttack.begin(); it != enemyAttack.end(); ++it)
    {
         if((*it)->m_CoolDown==0)
         {
             player->isHitting=false;
            enemyAttack.erase(it);
            --it;
         }
    }

    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->getAttackBox(),(*it)->GetCollider()->Get()) && !(*it)->isHitting)
        {
            (*it)->updateHealth(10);
          (*it)->isHitting = true;
        }
    }
   for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      if((*it)->getHealth()<=0)
     {
       ItemArr.push_back(new Item(new Properties("coin",(*it)->GetTransform()->X,(*it)->GetTransform()->Y,16,16)));
         delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
        enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
     }
   }

    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->getAttackBox()) && !player->isHitting)
        {
            player->isHitting=true;
           player->updateHealth(1);
        }
    }

     for(auto it = ItemArr.begin(); it != ItemArr.end();it++)
  {
     if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->m_Collider->Get()))
        {
                CoinCount++;
            delete (*it);
         (*it) = nullptr;
         ItemArr.erase(it);
         --it;
        }
  }
     player->Update(dt);
  for(auto it = enemyArr.begin(); it != enemyArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Update(dt);
  }
   for(auto it = ItemArr.begin(); it != ItemArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Update(dt);
  }
}

void GamePlay::draw()
{
    player->Draw();

    for(auto it = enemyArr.begin(); it != enemyArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Draw();
  }
   for(auto it = ItemArr.begin(); it != ItemArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Draw();
  }

}



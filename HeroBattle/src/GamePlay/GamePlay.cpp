#include "GamePlay.h"
#include "Engine.h"
#include"Collision.h"
#include <iostream>
#include"GameObject.h"
#include"TextureManager.h"
#include"Input.h"
#include<string>


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
         if((*it)->m_CoolDown==0 ||(*it)->getHealth()<=0)
         {
             player->isHitting=false;
//             delete(*it);
             (*it)=nullptr;
            enemyAttack.erase(it);
            --it;
         }
    }

    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->getAttackBox(),(*it)->GetCollider()->Get()) && !(*it)->isHitting)
        {
          (*it)->updateHealth(player->getAttack());
          (*it)->isHitting = true;
        }
    }
   for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      if((*it)->getHealth()<=0)
     {
       ItemArr.push_back(new Item(new Properties("coin",(*it)->GetTransform()->X+(rand()%40+1),(*it)->GetTransform()->Y,16,16)));
         delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
//        enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
     }
   }

    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->getAttackBox()) && !player->isHitting && !player->isDefending)
        {
            player->isHitting=true;
           player->updateHealth((*it)->getAttack());
        }
    }
//Item
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
// transition
  if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 )
  {
       Engine::GetInstance()->setMap("MAP");
       Collision::GetInstance()->init();
       player->m_Transform->X=50;
        for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
  }
  }
if( player->GetTransform()->X>=0 && player->GetTransform()->X<=40 )
  {
       Engine::GetInstance()->setMap("MAP2");
       Collision::GetInstance()->init();
       player->m_Transform->X=1800;
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



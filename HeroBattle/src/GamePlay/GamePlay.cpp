#include "GamePlay.h"
#include "Engine.h"
#include"Collision.h"
#include <iostream>
#include"GameObject.h"
#include"TextureManager.h"
#include"Input.h"
#include<string>
#include"LoadingState.h"


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
    for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
      delete (*it);
         (*it) = nullptr;
         bossArr.erase(it);
         --it;
    }
   for(int i=0;i<1;i++)
   {
       bossArr.push_back(new Boss(new Properties("boss",1000,0,100,180)));
   }
   for(int i=0;i<1;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
  }

}

void GamePlay::update(float dt)
{
// check melee attack once per game loop
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
    if(player->m_CoolDown==0)
    {
        (*it)->isHitting = false;
    }
    //push enemy to enemy attack arr
    if((*it)->isAttacking)  enemyAttack.push_back(*it);
    }

     for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
    if(player->m_CoolDown==0)
    {
        (*it)->isHitting = false;
    }
    //push enemy to enemy attack arr
    if((*it)->isAttacking) bossAttack.push_back(*it);
    }
//check enemy can attack player
     for(auto it = enemyAttack.begin(); it != enemyAttack.end(); ++it)
    {
         if((*it)->m_CoolDown==0 )
         {
             player->isHitting=false;
//             delete(*it);
             (*it)=nullptr;
            enemyAttack.erase(it);
            --it;
         }
    }
    for(auto it = bossAttack.begin(); it != bossAttack.end(); ++it)
    {
         if((*it)->m_CoolDown==0 )
         {
             player->isHitting=false;
//             delete(*it);
             (*it)=nullptr;
            bossAttack.erase(it);
            --it;
         }
    }
// check player attack
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->getAttackBox(),(*it)->GetCollider()->Get()) && !(*it)->isHitting )
        {
          (*it)->updateHealth(player->getAttack());
          (*it)->isHitting = true;
        }
    }
   for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->getAttackBox(),(*it)->GetCollider()->Get()) && !(*it)->isHitting )
        {
          (*it)->updateHealth(player->getAttack());
          (*it)->isHitting = true;
        }
    }
//check enemy dead
   for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      if((*it)->getHealth()<=0)
     {
       (*it)->isDied = true;
       (*it)->m_DiedAnimation-=dt;
       if((*it)->m_DiedAnimation<=0)
       {
         ItemArr.push_back(new Item(new Properties("coin",(*it)->GetTransform()->X+(rand()%40+1),(*it)->GetTransform()->Y,16,16)));
         delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
       }
//        enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96*2,0,96,64)));
     }
   }

//check enemy attack
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->getAttackBox()) && !player->isHitting && !player->isDefending)
        {
            player->isHitting=true;
           player->updateHealth((*it)->getAttack());
        }
    }
   for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
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
// transition map
if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP")){
  if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 )
  {
       Engine::GetInstance()->setMap("MAP2");
       Collision::GetInstance()->init();
       Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=50;
  }
}
else if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP2"))
{
    if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 )
  {
       Engine::GetInstance()->setMap("MAP3");
       Collision::GetInstance()->init();
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=50;
  }
  if( player->GetTransform()->X>=0 && player->GetTransform()->X<=40 )
  {
       Engine::GetInstance()->setMap("MAP");
       Collision::GetInstance()->init();
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=1820;
  }
}
else if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP3"))
{
     if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 )
  {
       Engine::GetInstance()->setMap("MAP4");
       Collision::GetInstance()->init();
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=50;
       player->m_Transform->Y=300;
  }
  if( player->GetTransform()->X>=0 && player->GetTransform()->X<=20 )
  {
       Engine::GetInstance()->setMap("MAP2");
       Collision::GetInstance()->init();
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=1820;
  }
}


//     if(boss1!= nullptr) boss1->Update(dt);
     if(player!=nullptr) player->Update(dt);
  for(auto it = enemyArr.begin(); it != enemyArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Update(dt);
  }
  for(auto it = bossArr.begin(); it != bossArr.end();it++)
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
   if(player!=nullptr) player->Draw();
//   if(boss1!= nullptr) boss1->Draw();
    for(auto it = enemyArr.begin(); it != enemyArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Draw();
  }
   for(auto it = bossArr.begin(); it != bossArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Draw();
  }
   for(auto it = ItemArr.begin(); it != ItemArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Draw();
  }

}

void GamePlay::close()
{
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
    }
    for(auto it = enemyAttack.begin(); it != enemyAttack.end(); ++it)
    {
         (*it) = nullptr;
         enemyAttack.erase(it);
         --it;
    }
    for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
      delete (*it);
         (*it) = nullptr;
         bossArr.erase(it);
         --it;
    }
    for(auto it = bossAttack.begin(); it != bossAttack.end(); ++it)
    {
         (*it) = nullptr;
         bossAttack.erase(it);
         --it;
    }
}



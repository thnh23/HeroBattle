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
     Engine::GetInstance()->setMap("MAP5");
       Collision::GetInstance()->init();
  player = new Knight(new Properties("knight",50,350,72,86));

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
    for(auto it = ItemArr.begin(); it != ItemArr.end(); ++it)
    {
      delete (*it);
         (*it) = nullptr;
         ItemArr.erase(it);
         --it;
    }

   for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96,400,96,64)));
  }
}

void GamePlay::update(float dt)
{
    // transition map
if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP")){
  if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 && enemyArr.empty() && bossArr.empty() )
  {
       Engine::GetInstance()->setMap("MAP2");
       Collision::GetInstance()->init();
        for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96,0,96,64)));
  }
    Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=50;
  }
}
else if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP2"))
{
    if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920 && enemyArr.empty() && bossArr.empty())
  {
       Engine::GetInstance()->setMap("MAP3");
       Collision::GetInstance()->init();
         for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96,0,96,64)));
  }
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
        player->m_Transform->X=50;
  }
  if( player->GetTransform()->X>=0 && player->GetTransform()->X<=40 )
  {
       Engine::GetInstance()->setMap("MAP");
       Collision::GetInstance()->init();
         for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96,0,96,64)));
  }
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=1820;
  }
}
else if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP3"))
{
     if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920&& enemyArr.empty() && bossArr.empty() )
  {
      Engine::GetInstance()->setMap("MAP4");
       Collision::GetInstance()->init();
       for(int i=0;i<10;i++)
  {
      enemyArr.push_back( new Enemy( new Properties("enemy",(rand()%1000+200)+96,0,96,64)));
  }
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
else if(Engine::GetInstance()->GetMap()==MapParser::GetInstance()->GetMap("MAP4"))
{
     if( player->GetTransform()->X>=1832 && player->GetTransform()->X<=1920&& enemyArr.empty() && bossArr.empty() )
  {
      Engine::GetInstance()->setMap("MAP5");
       Collision::GetInstance()->init();
       bossArr.push_back(new Boss(new Properties("boss",1000,0,100,180)));
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=50;
       player->m_Transform->Y=300;
  }
  if( player->GetTransform()->X>=0 && player->GetTransform()->X<=20 )
  {
       Engine::GetInstance()->setMap("MAP3");
       Collision::GetInstance()->init();
        Engine::GetInstance()->getStateMachine()->changeState(new LoadingState());
       player->m_Transform->X=1820;
  }
}

// check melee attack once per game loop
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
    if(player->m_CoolDown==0)
    {
        (*it)->isHitting = false;
    }
    if(player->getEnergy()==100)
    {
        (*it)->isSpecialHitting = false;
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
    if(player->getEnergy()==100)
    {
        (*it)->isSpecialHitting = false;
    }

    //push boss to boss attack arr
    if((*it)->isAttacking) bossAttack.push_back(*it);
    }
//check enemy can attack player
     for(auto it = enemyAttack.begin(); it != enemyAttack.end(); ++it)
    {
         if((*it)->m_CoolDown==0 )
         {
             player->isHitting=false;
             (*it)=nullptr;
            enemyAttack.erase(it);
            --it;
         }

    }
    for(auto it = bossAttack.begin(); it != bossAttack.end(); ++it)
    {
         if((*it)->m_CoolDown==0)
         {
             player->isHitting=false;
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
         if(Collision::GetInstance()->checkCollision(player->getSpecialAtkBox(),(*it)->GetCollider()->Get()) && !(*it)->isSpecialHitting)
        {
           (*it)->updateHealth(player->getSpecialAtk());
          (*it)->isSpecialHitting = true;
        }
    }
   for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->getAttackBox(),(*it)->GetCollider()->Get()) && !(*it)->isHitting )
        {
          (*it)->updateHealth(player->getAttack());
          (*it)->isHitting = true;
        }
         if(Collision::GetInstance()->checkCollision(player->getSpecialAtkBox(),(*it)->GetCollider()->Get()) && !(*it)->isSpecialHitting)
        {
           (*it)->updateHealth(player->getSpecialAtk());
          (*it)->isSpecialHitting = true;
        }
    }
//check enemy dead
   for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
      if((*it)->getHealth()<=0)
     {
         EnemyKill++;
       (*it)->isDied = true;
       (*it)->m_DiedAnimation-=dt;
       if((*it)->m_DiedAnimation<=0)
       {
           for(int i=0; i<rand()%5+1;i++) ItemArr.push_back(new Item(new Properties("coin",(*it)->GetTransform()->X+(rand()%40+1),(*it)->GetTransform()->Y,16,16)));
         delete (*it);
         (*it) = nullptr;
         enemyArr.erase(it);
         --it;
       }
     }
   }

//check enemy attack
    for(auto it = enemyArr.begin(); it != enemyArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->getAttackBox()) && !player->isHitting && !player->isDefending)
        {
            player->isHitting=true;
           player->updateHealth((*it)->getAttack());
            Mix_VolumeChunk(player->m_HittingSound,20);
             Mix_PlayChannel( -1,player->m_HittingSound,0);
        }
    }
    for(auto it = bossArr.begin(); it != bossArr.end(); ++it)
    {
        if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->getAttackBox()) && !player->isHitting && !player->isDefending)
        {
            player->isHitting=true;
           player->updateHealth((*it)->getAttack());
            Mix_VolumeChunk(player->m_HittingSound,20);
            Mix_PlayChannel( -1,player->m_HittingSound, 0 );
        }
    }
//Item
     for(auto it = ItemArr.begin(); it != ItemArr.end();it++)
  {
     if(Collision::GetInstance()->checkCollision(player->GetCollider()->Get(),(*it)->m_Collider->Get()))
        {
                CoinCount++;
                Mix_VolumeChunk((*it)->m_CoinSound,20);
                  Mix_PlayChannel( -1,(*it)->m_CoinSound, 0 );
            delete (*it);
         (*it) = nullptr;
         ItemArr.erase(it);
         --it;
        }
  }


//     if(boss1!= nullptr) boss1->Update(dt);
     if(player!=nullptr) player->Update(dt);
     for(auto it = bossArr.begin(); it != bossArr.end();it++)
  {
      if((*it) != nullptr )(*it)->Update(dt);
  }
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
   if(player!=nullptr) player->Draw();
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
    delete(player);
    player=nullptr;
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



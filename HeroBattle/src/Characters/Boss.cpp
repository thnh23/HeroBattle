#include "Boss.h"
#include"TextureManager.h"
#include"SDL.h"
#include<iostream>
#include"Collision.h"
#include"GamePlay.h"
#include"Camera.h"


Boss::Boss(Properties* props): Character(props)
{
     isAttacking = false;
    isDied = false;
    isHitting=false;
    isSpecialHitting=false;
    isSpecialAtk=false;
   m_AttackTime = BOSS_ATTACK_TIME;
   m_specialTime=3;
    m_Health = BOSS_HEALTH;
    m_CoolDown=0;
    m_Damage=10;
    m_Deffend=20;
    m_energy=0;

    m_Collider = new Collider();
    m_Collider->SetBuffer(45,70,-60,-80);

   m_RigidBody= new RigidBody();
   m_RigidBody->setGravity(5);

    m_Animation = new Animation();
   m_Animation->setProps(m_TextureID,1,8,100);

   m_SpecialAttackSound=Mix_LoadWAV("Maps/10_human_special_atk_1.wav");
   m_AttackSound=Mix_LoadWAV("Maps/17_orc_atk_sword_3.wav");
}

void Boss::Draw()
{
   if(isAttacking)
   {
       if(m_Flip == SDL_FLIP_NONE)
       m_Animation->Draw(m_Transform->X+20,m_Transform->Y,180,m_Height);
       else
          m_Animation->Draw(m_Transform->X-80,m_Transform->Y,180,m_Height);
   }
   else if(isSpecialAtk) m_Animation->Draw(m_Transform->X,m_Transform->Y,100,180);
   else if(isRunning) m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
   else  m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
 SDL_RenderFillRect(Engine::GetInstance()->getRenderer(),&health_box);
  Vector2D cam = Camera::GetInstance()->GetPos();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
//    box = attack_box;
//    box.x -= cam.X;
//    box.y -= cam.Y;
//  SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
}

void Boss::Update(float dt)
{
     if(m_Health<0) m_Health=0;
     //health bar
    Vector2D cam = Camera::GetInstance()->GetPos();
    health_box={m_Transform->X-cam.X+20,m_Transform->Y-cam.Y+80,(float)m_Health/1000*50,5};
   //  isSpecialAtk=true;
    isRunning=false;
 m_RigidBody->UnSetForce();

 m_energy+=0.05;
 if(m_energy>=100) m_energy=100;


if(m_energy==100 && (checkNearLeft(300) || checkNearRight(300)))
{
    m_RigidBody->UnSetForce();
    m_energy-=100;
    isSpecialAtk=true;
    GamePlay::GetInstance()->addEnemy(5);
     Mix_VolumeChunk(m_SpecialAttackSound,20);
    Mix_PlayChannel(-1,m_SpecialAttackSound,0);
}
if(m_specialTime>0 && isSpecialAtk)
{
    m_specialTime-=dt;
}else
{
    isSpecialAtk=false;
    m_specialTime=3;
}
//Follow player
 if(checkNearLeft(300)&& !isAttacking && !isSpecialAtk)
 {
    m_Flip = SDL_FLIP_HORIZONTAL;
    m_RigidBody->ApplyForceX(2*BACKWARD);
    isRunning=true;

 }else if(checkNearRight(300) &&!isAttacking && !isSpecialAtk) {
   m_Flip = SDL_FLIP_NONE;
   m_RigidBody->ApplyForceX(2*FORWARD);
   isRunning=true;
 }

 //attack
    if(Collision::GetInstance()->checkCollision(GamePlay::GetInstance()->getKnight()->GetCollider()->Get(),m_Collider->Get()) )
    {
        m_RigidBody->UnSetForce();
        m_Transform->X=m_LastSafePosition.X;
         Mix_VolumeChunk(m_AttackSound,20);
           Mix_PlayChannel(-1,m_AttackSound,0);
        if(m_CoolDown==0){
        isAttacking=true;
        m_CoolDown=2.5;
        }
    }
   if(m_CoolDown>0) m_CoolDown-=dt;
   else m_CoolDown=0;

    if(isAttacking && m_AttackTime >0 )
{
    m_AttackTime-=dt;
    if(m_Flip==SDL_FLIP_NONE) attack_box= {m_Transform->X+60,m_Transform->Y+70,70,m_Height-80};
    else  attack_box= {m_Transform->X,m_Transform->Y+70,70,m_Height-80};
}
else
{
    attack_box={0,0,0,0};
    isAttacking=false;
    m_AttackTime=BOSS_ATTACK_TIME;
}

 if(isHitting) m_RigidBody->UnSetForce();
 if(isDied) m_RigidBody->UnSetForce();
//set time

//update
  m_RigidBody->Update(0.6);
  m_LastSafePosition.X = m_Transform->X;
  m_Transform->X += m_RigidBody->Position().X;
  m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);


  if(Collision::GetInstance()->MapCollision(m_Collider->Get())){
         m_Transform->X = m_LastSafePosition.X;
  }

  m_RigidBody->Update(0.6);
  m_LastSafePosition.Y = m_Transform->Y;
  m_Transform->Y+=m_RigidBody->Position().Y;
  m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);
//map collision
  if(Collision::GetInstance()->MapCollision(m_Collider->Get())){
       m_Transform->Y = m_LastSafePosition.Y;
       isGround=true;
  }else{isGround=false;}


 AnimationState();
 m_Animation->Update();
}

void Boss::Clean()
{
      TextureManager::GetInstance()->Drop(m_TextureID);

}

void Boss::AnimationState()
{
     m_Animation->setProps("boss",1,8,120,m_Flip);
     if(isRunning) m_Animation->setProps("boss_run",1,10,100,m_Flip);
      if(isAttacking) m_Animation->setProps("boss_attack",1,17,100,m_Flip);
      if(isSpecialAtk) m_Animation->setProps("boss_special",1,19,100,m_Flip);
}

bool Boss::checkNearLeft(float distance)
{
   if( (m_Collider->Get().x+ m_Collider->Get().w) - (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) <=distance && (m_Collider->Get().x+ m_Collider->Get().w) - (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) >=0)
    {
        return true;
    }
    return false;
}

bool Boss::checkNearRight(float distance)
{
   if( -(m_Collider->Get().x+ m_Collider->Get().w) + (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) <=distance && -(m_Collider->Get().x+ m_Collider->Get().w) + (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) >=0)
     {
         return true;
     }

    return false;
}



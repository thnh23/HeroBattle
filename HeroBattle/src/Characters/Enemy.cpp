#include "Enemy.h"

#include"TextureManager.h"
#include"SDL.h"
#include<iostream>
#include"Collision.h"
#include"Knight.h"
#include"GamePlay.h"
#include"Camera.h"
#include"Timer.h"




Enemy::Enemy(Properties* props):Character(props)
{

    isAttacking = false;
   // m_JumpTime= JUMP_TIME_ENEMY;
   m_AttackTime = ENEMY_ATTACK_TIME;
    m_Health = ENEMY_HEALTH;

    m_Collider = new Collider();
    m_Collider->SetBuffer(30,15,-65,-15);

   m_RigidBody= new RigidBody();
   m_RigidBody->setGravity(5);

    m_Animation = new Animation();
   m_Animation->setProps(m_TextureID,1,8,100);
}

void Enemy::Draw()
{
     m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);

  Vector2D cam = Camera::GetInstance()->GetPos();
     SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
    box = attack_box;
    box.x -= cam.X;
    box.y -= cam.Y;
  SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
}

void Enemy::Update(float dt)
{
    isRunning=false;
 m_RigidBody->UnSetForce();

//Follow player
 if(checkNearLeft(200)&& !isAttacking)
 {
    m_Flip = SDL_FLIP_HORIZONTAL;
    m_RigidBody->ApplyForceX(2*BACKWARD);
    isRunning=true;

 }else if(checkNearRight(200) &&!isAttacking) {
   m_Flip = SDL_FLIP_NONE;
   m_RigidBody->ApplyForceX(2*FORWARD);
   isRunning=true;
 }

// if((checkNearLeft()||checkNearRight())&&m_Collider->Get().y+ m_Collider->Get().h >= GamePlay::GetInstance()->getKnight()->GetCollider()->Get().y+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().h && isGround)
// {
//    std::cout<<m_Collider->Get().y+ m_Collider->Get().h<<" "<< GamePlay::GetInstance()->getKnight()->GetCollider()->Get().y+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().h<<std::endl;
//    isGround=false;
//    isJumping=true;
//    m_RigidBody->ApplyForceY(10*UPWARD);
// }
//
// if( (checkNearLeft()||checkNearRight()) &&m_Collider->Get().y+ m_Collider->Get().h>= GamePlay::GetInstance()->getKnight()->GetCollider()->Get().y+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().h&& isJumping && m_JumpTime>0)
//{
//    m_JumpTime-=dt;
//     m_RigidBody->ApplyForceY(UPWARD*10);
//}
//else
//{
//    m_JumpTime=JUMP_TIME_ENEMY;
//    isJumping=false;
//}

 //attack
    if(Collision::GetInstance()->checkCollision(GamePlay::GetInstance()->getKnight()->GetCollider()->Get(),m_Collider->Get()) )
    {
        m_RigidBody->UnSetForce();
        m_Transform->X=m_LastSafePosition.X;
        isAttacking=true;
    }

    if(isAttacking && m_AttackTime >0 )
{
    m_AttackTime-=dt;
    if(m_Flip==SDL_FLIP_NONE) attack_box= {m_Transform->X+50,m_Transform->Y+15,m_Width-70,m_Height-15};
        else  attack_box= {m_Transform->X+18,m_Transform->Y+15,m_Width-70,m_Height-15};
}
else
{
    attack_box={0,0,0,0};
    isAttacking=false;
    m_AttackTime=ENEMY_ATTACK_TIME;
}



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

void Enemy::Clean()
{
      TextureManager::GetInstance()->Drop(m_TextureID);

}

void Enemy::AnimationState()
{
     m_Animation->setProps("enemy",1,8,120,m_Flip);
     if(isRunning) m_Animation->setProps("enemy_run",1,10,100,m_Flip);
     if(isAttacking) m_Animation->setProps("enemy_attack",1,10,100,m_Flip);
}

bool Enemy::checkNearLeft(float distance)
{
   if( (m_Collider->Get().x+ m_Collider->Get().w) - (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) <=distance && (m_Collider->Get().x+ m_Collider->Get().w) - (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) >=0)
    {
        return true;
    }
    return false;
}

bool Enemy::checkNearRight(float distance)
{
   if( -(m_Collider->Get().x+ m_Collider->Get().w) + (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) <=distance && -(m_Collider->Get().x+ m_Collider->Get().w) + (GamePlay::GetInstance()->getKnight()->GetCollider()->Get().x+GamePlay::GetInstance()->getKnight()->GetCollider()->Get().w) >=0)
     {
         return true;
     }

    return false;
}


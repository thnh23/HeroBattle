#include"Knight.h"
#include"TextureManager.h"
#include"SDL.h"
#include"Input.h"
#include"Engine.h"
#include"Camera.h"
#include"Collision.h"
#include"GamePlay.h"



Knight::Knight(Properties* props):Character(props)
{
    isAttacking=false;
    isDied = false;
    isSpecialAtk=false;

    m_JumpForce = JUMP_FORCE;
    m_JumpTime =JUMP_TIME;
    m_AttackTime=ATTACK_TIME;
    m_Health =MAX_HEALTH;
    m_DiedAnimation= 1.5;
    m_SpecialAnimation=3;

    m_CoolDown=0;
    m_Deffend=0;
    m_Damage = 10;
    m_energy = 0;

    m_Collider = new Collider();
     m_Collider->SetBuffer(20,12,-42,-15);

   m_RigidBody= new RigidBody();
   m_RigidBody->setGravity(3);

    m_Animation = new Animation();
   m_Animation->setProps(m_TextureID,1,7,100);

   specialAnimation= new Animation();

   m_AttackSound= Mix_LoadWAV("Maps/26_sword_hit_1.wav");
   m_UpdagreSound = Mix_LoadWAV("Maps/08_human_charge_1.wav");
   m_SpecialAttackSound = Mix_LoadWAV("Maps/10_human_special_atk_2.wav");
   m_HittingSound = Mix_LoadWAV("Maps/11_human_damage_1.wav");
   m_JumpSound = Mix_LoadWAV("Maps/12_human_jump_1.wav");
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
    if(isSpecialAtk) specialAnimation->Draw(special_attack_box.x,special_attack_box.y,82,48);

// Vector2D cam = Camera::GetInstance()->GetPos();
//   SDL_Rect box = special_attack_box;
//   box.x -= cam.X;
//   box.y -= cam.Y;
//       SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
//  box = attack_box;
//  box.x -= cam.X;
//   box.y -= cam.Y;
// std::cout<<attack_box.x<<" "<<attack_box.y<<" "<<attack_box.w<<" "<<attack_box.h<<std::endl;
 //SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);

}

void Knight::Update(float dt)
{
    isRunning = false;
    isDefending=false;
    m_RigidBody->UnSetForce();
    m_RigidBody->UnSetFriction();
    m_SpecialDamage=m_Damage*2;
// setup
if(m_Health<0) m_Health=0;
if(m_Health>MAX_HEALTH) m_Health=MAX_HEALTH;
//energy
m_energy+=0.02;
if(m_energy>=100) m_energy=100;
 //move
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !isAttacking)
 {
       m_Flip = SDL_FLIP_HORIZONTAL;
    m_RigidBody->ApplyForceX(2*BACKWARD);
    isRunning=true;
 }
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && !isAttacking)
 {
      m_Flip =SDL_FLIP_NONE;
    m_RigidBody->ApplyForceX(2*FORWARD);
    isRunning = true;
 }

//Attack
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)&& m_CoolDown==0)
 {
     m_RigidBody->UnSetForce();
    isAttacking=true;
    m_CoolDown=0.75;
     Mix_PlayChannel( -1, m_AttackSound, 0 );
 }

  if(m_CoolDown>0) m_CoolDown-=dt;
   else m_CoolDown=0;

 if(isAttacking && m_AttackTime >0 )
{
    m_AttackTime-=dt;
     if(m_Flip==SDL_FLIP_NONE) attack_box={m_Transform->X+40,m_Transform->Y+15,m_Width-30,m_Height-15};
   else attack_box={m_Transform->X-5,m_Transform->Y+15,m_Width-30,m_Height-15};
}
else
{
    attack_box={0,0,0,0};
    isAttacking=false;
    m_AttackTime=ATTACK_TIME;
}

if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_energy==100)
 {
     m_RigidBody->UnSetForce();
     isSpecialAtk=true;
    m_energy-=100;
     Mix_VolumeChunk(m_SpecialAttackSound,50);
     Mix_PlayChannel( -1, m_SpecialAttackSound, 0 );
     if(m_Flip==SDL_FLIP_NONE)
   {
       isLeft=false;
       special_attack_box={m_Transform->X+60,m_Transform->Y+15,m_Width,m_Height-15};
   }
   else
   {
       isLeft=true;
       special_attack_box={m_Transform->X-5,m_Transform->Y+15,m_Width,m_Height-15};
   }
 }
if(isSpecialAtk&& m_SpecialAnimation>0)
{
    m_SpecialAnimation-=dt;
    if(!isLeft)
    {
        special_attack_box.x+=4;
    }else special_attack_box.x-=4;
}
else
{
    special_attack_box={0,0,0,0};
    isSpecialAtk=false;
    m_SpecialAnimation=3;
}
//jump
if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && isGround )
{
    isGround = false;
    isJumping=true;
    m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
     Mix_VolumeChunk(m_JumpSound,60);
     Mix_PlayChannel( -1, m_JumpSound, 0 );
}
if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && isJumping && m_JumpTime>0)
{
    m_JumpTime-=dt;
     m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
}
else
{
    m_JumpTime=JUMP_TIME;
    isJumping=false;
}
 //Defend
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
  {
      isDefending =true;
      m_RigidBody->UnSetForce();
  }

//fall
   if(m_RigidBody->Velocity().Y>0 && !isGround)
   {
       isFalling=true;
   }else isFalling = false;

//update
  m_RigidBody->Update(0.8);
  m_LastSafePosition.X = m_Transform->X;
  m_Transform->X += m_RigidBody->Position().X;
  m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);


  if(Collision::GetInstance()->MapCollision(m_Collider->Get())){
        m_Transform->X = m_LastSafePosition.X;
  }

  m_RigidBody->Update(0.8);
  m_LastSafePosition.Y = m_Transform->Y;
  m_Transform->Y+=m_RigidBody->Position().Y;
  m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);

  if(Collision::GetInstance()->MapCollision(m_Collider->Get())){
        isGround = true;
     m_Transform->Y = m_LastSafePosition.Y;
  }else{ isGround = false;}


 m_Origin->X= m_Transform->X +m_Width/2;
 m_Origin->Y = m_Transform->Y + m_Height/2;
 AnimationState();
 m_Animation->Update();
 specialAnimation->Update();
}

void Knight::AnimationState()
{
        m_Animation->setProps("knight",1,4,120,m_Flip);
    if(isRunning)
        m_Animation->setProps("knight_run",1,7,120,m_Flip);
    if(isFalling)
         m_Animation->setProps("knight_fall",1,3,120,m_Flip);
    if(isJumping)
        m_Animation->setProps("knight_jump",1,3,120,m_Flip);
    if(isDefending)
       m_Animation->setProps("knight_defend",1,5,120,m_Flip);
    if(isAttacking)
        m_Animation->setProps("knight_attack1",1,5,120,m_Flip);
    if(isDied)
            m_Animation->setProps("knight_die",1,6,120,m_Flip);
    if(isSpecialAtk)
         specialAnimation->setProps("knight_special",1,5,120,m_Flip);
}


void Knight::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}

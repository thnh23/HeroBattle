#include"Knight.h"
#include"TextureManager.h"
#include"SDL.h"
#include"Input.h"
#include"Engine.h"
#include"Camera.h"
#include"Collision.h"
#include"GamePlay.h"
#include"Timer.h"


Knight::Knight(Properties* props):Character(props)
{
    isAttacking=false;

    m_JumpForce = JUMP_FORCE;
    m_JumpTime =JUMP_TIME;
    m_AttackTime=ATTACK_TIME;
    m_Health =MAX_HEALTH;
    m_CoolDown=0;

    m_Collider = new Collider();
     m_Collider->SetBuffer(20,12,-35,-15);

   m_RigidBody= new RigidBody();
   m_RigidBody->setGravity(3);

    m_Animation = new Animation();
   m_Animation->setProps(m_TextureID,1,7,100);
}

void Knight::Draw()
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
// std::cout<<attack_box.x<<" "<<attack_box.y<<" "<<attack_box.w<<" "<<attack_box.h<<std::endl;
 SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);

}

void Knight::Update(float dt)
{
    isRunning = false;
    isDefending=false;
    m_RigidBody->UnSetForce();

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
    m_CoolDown=0.5;
 }

  m_CoolDown-=dt;
  if(m_CoolDown<=0) m_CoolDown=0;

 if(isAttacking && m_AttackTime >0 )
{
    m_AttackTime-=dt;
     if(m_Flip==SDL_FLIP_NONE) attack_box={m_Transform->X+40,m_Transform->Y+15,m_Width-35,m_Height-15};
   else attack_box={m_Transform->X,m_Transform->Y+15,m_Width-35,m_Height-15};

}
else
{
    attack_box={0,0,0,0};
    isAttacking=false;
    isAttacking=false;
    m_AttackTime=ATTACK_TIME;
}

 //Defend
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
  {
      isDefending =true;
      m_RigidBody->UnSetForce();

  }

//jump
if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && isGround )
{
    isGround = false;
    isJumping=true;
    m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
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
}

void Knight::AnimationState()
{
        m_Animation->setProps("knight",1,4,120,m_Flip);
    if(isRunning)
        m_Animation->setProps("knight_run",1,7,120,m_Flip);
    if(isFalling)
         m_Animation->setProps("knight_fall",1,3,250,m_Flip);
    if(isJumping)
        m_Animation->setProps("knight_jump",1,3,200,m_Flip);
    if(isDefending)
      m_Animation->setProps("knight_defend",1,5,200,m_Flip);
    if(isAttacking)
        m_Animation->setProps("knight_attack1",1,5,120,m_Flip);
}


void Knight::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}

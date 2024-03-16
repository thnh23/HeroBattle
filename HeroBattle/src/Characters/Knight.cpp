#include"Knight.h"
#include"TextureManager.h"
#include"SDL.h"
#include"Input.h"

Knight::Knight(Properties* props):Character(props)
{
   m_RigidBody= new RigidBody();
    m_Animation = new Animation();
   m_Animation->setProps(m_TextureID,1,7,100);
}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
}

void Knight::Clean()
{
    TextureManager::GetInstance()->Clean();
}

void Knight::Update(float dt)
{
     m_Animation->setProps("knight",1,4,100);
     m_RigidBody->UnSetForce();
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
 {
    m_Animation->setProps("knight_run",1,7,100,SDL_FLIP_HORIZONTAL);
    m_RigidBody->ApplyForceX(5*BACKWARD);
 }
 if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
 {
    m_Animation->setProps("knight_run",1,7,100);
    m_RigidBody->ApplyForceX(5*FORWARD);
 }
  if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
  {
     m_Animation->setProps("knight_jump",1,6,100);
     m_RigidBody->ApplyForceY(UPWARD);
  }
  if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
  {
     m_Animation->setProps("knight_defend",1,5,100);
     m_RigidBody->ApplyForceY(DOWNWARD);
  }

m_RigidBody->Update(dt);
m_Transform->TranslateX(m_RigidBody->Position().X);
 m_Transform->TranslateY(m_RigidBody->Position().Y);
 m_Animation->Update();
}

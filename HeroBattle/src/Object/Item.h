#ifndef ITEM_H
#define ITEM_H

#include"GameObject.h"
#include"TextureManager.h"
#include"Collider.h"
#include"Camera.h"
#include"Collider.h"
#include"RigidBody.h"
#include"Collision.h"
#include"SDL_mixer.h"
class Item : public GameObject
{
public:

    Item(Properties* props):GameObject(props)
    {
        m_Collider = new Collider();
        m_Collider->SetBuffer(0,0,0,0);

        m_RigidBody= new RigidBody();
        m_RigidBody->setGravity(3);

        m_Animation = new Animation();
        m_Animation->setProps(m_TextureID,1,7,100);
    }

    virtual void Draw()
    {
        m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);

//        Vector2D cam = Camera::GetInstance()->GetPos();
//        SDL_Rect box = m_Collider->Get();
//        box.x -= cam.X;
//        box.y -= cam.Y;
//        SDL_RenderDrawRect(Engine::GetInstance()->getRenderer(),&box);
    };
    virtual void Update(float dt)
    {
        m_RigidBody->Update(0.8);
        m_LastSafePosition.X = m_Transform->X;
        m_Transform->X += m_RigidBody->Position().X;
        m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);


        if(Collision::GetInstance()->MapCollision(m_Collider->Get()))
        {
            m_Transform->X = m_LastSafePosition.X;
        }

        m_RigidBody->Update(0.8);
        m_LastSafePosition.Y = m_Transform->Y;
        m_Transform->Y+=m_RigidBody->Position().Y;
        m_Collider->Set(m_Transform->X, m_Transform->Y,m_Width,m_Height);

        if(Collision::GetInstance()->MapCollision(m_Collider->Get()))
        {
            m_Transform->Y = m_LastSafePosition.Y;
        }

        m_Origin->X= m_Transform->X +m_Width/2;
        m_Origin->Y = m_Transform->Y + m_Height/2;
        m_Animation->setProps("coin",1,5,100);
        m_Animation->Update();
    }

    virtual void Clean()
    {
        TextureManager::GetInstance()->Drop(m_TextureID);
    }
    Collider* m_Collider;
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Vector2D m_LastSafePosition;
   virtual ~Item(){}
   Mix_Chunk* m_CoinSound = Mix_LoadWAV("Maps/collect-points-190037.mp3");
};

#endif // ITEM_H

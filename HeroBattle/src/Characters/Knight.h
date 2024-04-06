
#ifndef KNIGHT_H
#define KNIGHT_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"

const float JUMP_FORCE = 4;
const float JUMP_TIME = 0.5;
const float ATTACK_TIME = 0.5;
const int MAX_HEALTH=1000;

class Knight : public Character
{
    public:

     Knight(Properties* props);
      virtual void Draw();
      virtual void Update(float dt);
      virtual void Clean();
      Collider* GetCollider(){return m_Collider;}
      Vector2D getSafePosition(){return m_LastSafePosition;}
       Transform* GetTransform(){return m_Transform;}
       int getHealth(){return m_Health;}
       void updateHealth(int damage){m_Health-=damage;}
       SDL_Rect getAttackBox(){return attack_box;}
        void setAttackBox(){attack_box={0,0,0,0};}


    private:
        void AnimationState();

        bool isJumping;
        bool isGround;
        bool isAttacking;
        bool isDefending;
        bool isFalling;
        bool isRunning;


        float m_JumpForce ;
        float m_JumpTime;
        float m_AttackTime;
        float m_CoolDown;
        int m_Health;

      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
};


#endif

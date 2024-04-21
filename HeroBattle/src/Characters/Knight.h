
#ifndef KNIGHT_H
#define KNIGHT_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"

const float JUMP_FORCE = 5;
const float JUMP_TIME = 0.5;
const float ATTACK_TIME = 0.5;
const int MAX_HEALTH=100;
const float DEFFEND_TIME = 1;


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
       void updateHealth(int damage)
       {
           if(damage- m_Deffend<1) m_Health-=1;
           else m_Health-=(damage-m_Deffend);
       }

       int getAttack(){return m_Damage;}
       void updateAttack(int x){m_Damage+=x;}
        int getDeffend(){return m_Deffend;}
         void updateDeffend(int shield){m_Deffend+=shield;}

       SDL_Rect getAttackBox(){return attack_box;}

        void AnimationState();

        bool isJumping;
        bool isGround;
        bool isAttacking;
        bool isDefending;
        bool isFalling;
        bool isRunning;
        bool isHitting;
        bool isDied;


        float m_JumpForce ;
        float m_JumpTime;
        float m_AttackTime;
        float m_CoolDown;
        float m_DeffendTime;
        float m_DiedAnimation;
        int m_Health;
        int m_Deffend;
        int m_Damage;

      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
};


#endif

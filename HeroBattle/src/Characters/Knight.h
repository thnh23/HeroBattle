
#ifndef KNIGHT_H
#define KNIGHT_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"
#include"SDL_mixer.h"

const float JUMP_FORCE = 5;
const float JUMP_TIME = 0.5;
const float ATTACK_TIME = 0.5;
const int MAX_HEALTH=100;



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
       float getHealth(){return m_Health;}
       void updateHealth(float damage)
       {
           if(damage- m_Deffend<1) m_Health-=1;
           else m_Health-=(damage-m_Deffend);
       }
       void healing(float heal)
       {
           m_Health+=heal;
       }

       float getAttack(){return m_Damage;}
       float getSpecialAtk(){return m_SpecialDamage;}
       void updateAttack(float x){m_Damage+=x;}
        float getDeffend(){return m_Deffend;}
         void updateDeffend(float shield){m_Deffend+=shield;}
         float getEnergy(){return m_energy;}

       SDL_Rect getAttackBox(){return attack_box;}
       SDL_Rect getSpecialAtkBox(){return special_attack_box;}

        void AnimationState();

        bool isJumping;
        bool isGround;
        bool isAttacking;
        bool isDefending;
        bool isFalling;
        bool isRunning;
        bool isHitting;
        bool isDied;
        bool isSpecialAtk;


        float m_JumpForce ;
        float m_JumpTime;
        float m_AttackTime;
        float m_CoolDown;
        float m_DiedAnimation;
        float m_SpecialAnimation;
        float m_Health;
        float m_Deffend;
        float m_Damage;
        float m_SpecialDamage;
        float m_energy;

      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
      SDL_Rect special_attack_box;
      Animation* specialAnimation;
      Mix_Chunk* m_AttackSound;
      Mix_Chunk* m_UpdagreSound;
      Mix_Chunk* m_SpecialAttackSound;
      Mix_Chunk* m_HittingSound;
};


#endif

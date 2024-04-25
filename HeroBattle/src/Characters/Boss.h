#ifndef BOSS_H
#define BOSS_H


#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"
#include"SDL_mixer.h"

const int BOSS_HEALTH=1000;
const float BOSS_ATTACK_TIME=1.5;


class Boss : public Character
{
    public:

     Boss(Properties* props);
      virtual ~Boss(){}
      virtual void Draw();
      virtual void Update(float dt);
      virtual void Clean();
     Collider* GetCollider(){return m_Collider;}
     Vector2D getSafePosition(){return m_LastSafePosition;}
      Transform* GetTransform(){return m_Transform;}
        SDL_Rect getAttackBox(){return attack_box;}

      bool checkNearLeft(float distance);
      bool checkNearRight(float distance);

       int getHealth(){return m_Health;}
       void updateHealth(int damage){m_Health-=damage;}
        int getAttack(){return m_Damage;}
       void updateAttack(int x){m_Health+=x;}
        int getDeffend(){return m_Deffend;}
         void updateDeffend(int shield){m_Deffend+=shield;}


     void AnimationState();

     bool isAttacking;
     bool isGround;
     bool isRunning;
     bool isHitting;
      bool isDied;
      bool isSpecialHitting;
      bool isSpecialAtk;
     int m_Health;
     float m_AttackTime;
     float m_CoolDown;
     float m_DiedAnimation;
     int m_Damage;
     int m_Deffend;
     float m_energy;
     float m_specialTime;



      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
      SDL_Rect health_box;

      Mix_Chunk* m_AttackSound;
      Mix_Chunk* m_SpecialAttackSound;

};


#endif // BOSS_H

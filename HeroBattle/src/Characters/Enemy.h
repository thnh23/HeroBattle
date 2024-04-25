
#ifndef ENEMY_H
#define ENEMY_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"
#include"SDL_mixer.h"


const int ENEMY_HEALTH=30;
const float ENEMY_ATTACK_TIME=1.5;


class Enemy : public Character
{
    public:

     Enemy(Properties* props);
      virtual ~Enemy(){}
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

  //  int m_JumpTime;
    int m_Health;
     float m_AttackTime;
     float m_CoolDown;
     float m_DiedAnimation;
     int m_Damage;
     int m_Deffend;



      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
      SDL_Rect health_box;

      Mix_Chunk* m_AttackSound;
      Mix_Chunk* m_DeadSound;
};


#endif


#ifndef ENEMY_H
#define ENEMY_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"

//const float JUMP_TIME_ENEMY = 30;
const int ENEMY_HEALTH=500;
const float ENEMY_ATTACK_TIME=0.5;


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

    private:
     void AnimationState();

     bool isAttacking;
     bool isGround;
     bool isRunning;
  //   bool isJumping;

  //  int m_JumpTime;
    int m_Health;
     float m_AttackTime;



      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
      SDL_Rect attack_box;
};


#endif

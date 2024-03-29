#ifndef KNIGHT_H
#define KNIGHT_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"
#include"Collider.h"


const float JUMP_FORCE = 8;
const float JUMP_TIME = 20;
const float ATTACK_TIME = 32;
class Knight : public Character
{
    public:

     Knight(Properties* props);
      virtual void Draw();
      virtual void Update(float dt);
      virtual void Clean();

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

      Collider* m_Collider;
      Animation* m_Animation;
      RigidBody* m_RigidBody;
      Vector2D m_LastSafePosition;
};


#endif

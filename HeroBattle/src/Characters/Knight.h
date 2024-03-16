#ifndef KNIGHT_H
#define KNIGHT_H
#include"Character.h"
#include"Animation.h"
#include"RigidBody.h"

class Knight : public Character
{
    public:

     Knight(Properties* props);
     virtual void Draw();
    virtual void Update(float dt);
    virtual void Clean();

    private:
      Animation* m_Animation;
      RigidBody* m_RigidBody;
};


#endif

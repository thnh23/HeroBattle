#ifndef COLLISION_H
#define COLLISION_H

#include"SDL.h"
#include<vector>
#include"TileLayer.h"
#include"GameMap.h"


class Collision
{
    public:
       bool checkCollision(SDL_Rect a, SDL_Rect b);
       bool MapCollision(SDL_Rect a);

     inline static Collision* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new Collision();
  }

    private:
        static Collision* m_Instance;
        Collision();
        TileMap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
};

#endif // COLLISION_H

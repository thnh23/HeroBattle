#include "Collision.h"
#include"Engine.h"
#include<iostream>

 Collision* Collision::m_Instance=nullptr;
Collision::Collision()
{
    m_CollisionLayer=(TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
    m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

bool Collision::checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps =(a.x <b.x + b.w) && (a.x + a.w >b.x);
    bool y_overlaps = (a.y< b.y+ b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool Collision::MapCollision(SDL_Rect a)
{
    int tileSize = 32;
    int rowCount = 20;
    int ColCount = 60;

    int left_tile = a.x/tileSize;
    int right_tile =(a.x+a.w)/tileSize;

    int top_tile= a.y/tileSize;
    int bottom_tile = (a.y +a.h)/tileSize;

    if(left_tile<0) left_tile=0;
    if(right_tile>ColCount) right_tile = ColCount;

    if(top_tile<0) top_tile=0;
    if(bottom_tile>rowCount) bottom_tile = rowCount;

    for(int i=left_tile;i<=right_tile;i++)
    {
      for(int j=top_tile;j<=bottom_tile;j++)
      {
          if(m_CollisionTilemap[j][i]>0)
          {
              return true;
          }
      }
    }
    return false;
}

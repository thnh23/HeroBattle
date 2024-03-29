#ifndef CAMERA_H
#define CAMERA_H

#include"Point.h"
#include"Vector2D.h"
#include "SDL.h"
#include"Engine.h"

class Camera
{
    public:
      inline static Camera* GetInstance(){return m_Instance =(m_Instance!=nullptr) ? m_Instance : new Camera();}
      inline SDL_Rect GetViewBox(){return m_ViewBox;}
      inline Vector2D GetPos(){return m_Position;}
      inline void  SetTarget(Point* target) { m_Target = target;}
      void Update(float dt);
    private:
         Camera(){m_ViewBox ={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};}

         SDL_Rect m_ViewBox;
         Point* m_Target;
         Vector2D m_Position;
         static Camera* m_Instance;
};

#endif // CAMERA_H

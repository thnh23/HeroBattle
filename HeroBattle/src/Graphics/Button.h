
#ifndef BUTTON_H
#define BUTTON_H

#include"Input.h"
#include"TextureManager.h"
#include"SDL_mixer.h"
class Button
{
    public:
    Button(std::string TEX_ID, int X, int Y, int W, int H, float SCALE)
    {
   curFrame = MOUSE_OUT;
   scale = SCALE;
   rect ={X,Y,W,H};
   textureID =TEX_ID;
    }
    virtual ~Button(){};
    virtual void draw()
    {
           TextureManager::GetInstance()->DrawFrameNoCamera(textureID,rect.x,rect.y,rect.w,rect.h,curRow,curFrame);
    }
     bool checkCollision(Vector2D* vec)
{
       if (vec->X > rect.x
              && vec->X < rect.x + rect.w
              && vec->Y > rect.y
              && vec->Y < rect.y + rect.h)
       {
              return true;
       }
       return false;
}
    virtual void update()
    {
         if(checkCollision(Input::GetInstance()->getMousePos()))
       {
              if (Input::GetInstance()->getMouseButtonState(LEFT))
              {
                     curFrame = MOUSE_DOWN;
                     released = false;
              }
              else
              {
                     released = true;
                     curFrame = MOUSE_OVER;
              }
       }
       else
       {
              curFrame = MOUSE_OUT;
       }
    }
    virtual void clean(){}


    private:

    bool released;
    enum button_state
{
       MOUSE_OUT = 0,
       MOUSE_OVER = 1,
       MOUSE_DOWN = 2
};
 int curRow = 1, curFrame = 0;
       SDL_Rect rect;
       float scale = 1;
       std::string textureID;
};


#endif // BUTTON_H

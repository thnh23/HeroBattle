//#ifndef BUTTON_H
//#define BUTTON_H
//#include"SDL.h"
//
//typedef struct {
//    SDL_Rect draw_rect;    // dimensions of button
//    struct {
//        Uint8 r, g, b, a;
//    } colour;
//
//    bool pressed;
//} Button;
//
//static void Button_process_event(Button *btn, const SDL_Event *ev) {
//    if(ev->type == SDL_MOUSEBUTTONDOWN) {
//        if(ev->button.button == SDL_BUTTON_LEFT &&
//                ev->button.x >= btn->draw_rect.x &&
//                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
//                ev->button.y >= btn->draw_rect.y &&
//                ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
//            btn->pressed = true;
//        }
//    }
//}
//
//static bool button(SDL_Renderer *r, Button *btn) {
//    // draw button
//    SDL_SetRenderDrawColor(r, btn->colour.r, btn->colour.g, btn->colour.b, btn->colour.a);
//    SDL_RenderFillRect(r, &btn->draw_rect);
//
//    // if button press detected - reset it so it wouldn't trigger twice
//    if(btn->pressed) {
//        btn->pressed = false;
//        return true;
//    }
//    return false;
//}
//
//#endif // BUTTON_H

#ifndef BUTTON_H
#define BUTTON_H

#include"Input.h"
#include"TextureManager.h"
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

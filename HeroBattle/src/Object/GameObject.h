#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include"IObject.h"
#include"Transform.h"
#include"SDL.h"
struct Properties
{
    public:
     std::string TextureID;
     int Width, Height;
     float X,Y;
     SDL_RendererFlip Flip;
    public:
    Properties(std::string textureID,int x,int y, int width, int height, SDL_RendererFlip flip =SDL_FLIP_NONE)
    {
        X=x;
        Y=y;
        Width=width;
        Height=height;
        Flip=flip;
        TextureID=textureID;
    }
};
//abstract class

 class GameObject : public IObject
 {
    protected:
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;

   public:
   GameObject(Properties* props): m_TextureID(props->TextureID), m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip)
   {
      m_Transform = new Transform(props->X,props->Y);
   }
   public:
   virtual void Draw()=0;
    virtual void Update(float dt)=0;
    virtual void Clean()=0;

 };


#endif

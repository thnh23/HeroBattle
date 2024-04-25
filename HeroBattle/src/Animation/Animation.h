#ifndef ANIMATION_H
#define ANIMATION_H
#include<string>
#include"SDL.h"
class Animation
{
    public:
  Animation(){}
  void Update();
  void Draw(float x, float y, int spriteWidth, int SpriteHeight);
  void DrawNoCamera(float x, float y, int spriteWidth, int SpriteHeight);
  void setProps(std::string textureID, int spriteRow, int frame, int animSpeed, SDL_RendererFlip flip =SDL_FLIP_NONE);

private:
int  m_SpriteRow, m_SpriteFrame;
int m_AnimSpeed, m_FrameCount;
std::string m_TextureID;
SDL_RendererFlip m_Flip;
};

#endif

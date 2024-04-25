#include"Animation.h"
#include"TextureManager.h"
#include<iostream>
void Animation::Update()
{
    m_SpriteFrame= (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
TextureManager::GetInstance()->DrawFrame(m_TextureID,x,y,spriteWidth,spriteHeight,m_SpriteRow,m_SpriteFrame,m_Flip);
}

void Animation::DrawNoCamera(float x, float y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrameNoCamera(m_TextureID,x,y,spriteWidth,spriteHeight,m_SpriteRow,m_SpriteFrame,m_Flip);
}

void Animation::setProps(std::string textureID, int spriteRow, int frame, int animSpeed, SDL_RendererFlip flip  )
{
    m_TextureID=textureID;
    m_SpriteRow=spriteRow;
    m_FrameCount=frame;
    m_AnimSpeed=animSpeed;
    m_Flip=flip;
}

#include "Camera.h"

Camera* Camera::m_Instance = nullptr;

void Camera::Update()
{
    if(m_Target != nullptr)
    {
        m_ViewBox.x = m_Target->X - SCREEN_WIDTH/2;
        m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT/2;
        if(m_ViewBox.x <64)  m_ViewBox.x=64;
        if(m_ViewBox.y<32)  m_ViewBox.y=32;
        if(m_ViewBox.x>58*32 - m_ViewBox.w)
        {
          m_ViewBox.x = 58*32 -m_ViewBox.w;
        }
        if(m_ViewBox.y > 20*32 -m_ViewBox.h)
        {
            m_ViewBox.y = 20*32 - m_ViewBox.h;
        }
        m_Position = Vector2D(m_ViewBox.x,m_ViewBox.y);
    }
}

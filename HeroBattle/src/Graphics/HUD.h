#ifndef HUD_H
#define HUD_H
#include"Timer.h"

class HUD
{
    public:
         static HUD* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new HUD();
  }
      void  initHUD();
      void  updateHUD();
    void  drawHUD();
    Timer* getTimer(){return &m_Timer;}
   private:
         int coin;
         int health;
         static HUD* m_Instance;
        Timer m_Timer;
        int minute, second;
        std::string time;
        float energy;
};

#endif // HUD_H

#ifndef HUD_H
#define HUD_H


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
   private:
         int coin;
         int health;
         static HUD* m_Instance;

};

#endif // HUD_H

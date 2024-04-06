#ifndef TIMER_H
#define TIMER_H

#include <iostream>

class Timer
{
    public:
        float getTime();

        inline static Timer* GetInstance(){return (m_Instance != nullptr)?m_Instance : new Timer();}
   private:
      Timer(){};
      static Timer* m_Instance;
};



#endif

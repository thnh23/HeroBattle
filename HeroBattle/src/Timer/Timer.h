#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include"SDL.h"
class Timer
{
    public:
        float getTime();
        //Initializes variables
        Timer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

        inline static Timer* GetInstance(){return (m_Instance != nullptr)?m_Instance : new Timer();}
   private:

      static Timer* m_Instance;

      //The clock time when the timer started
        Uint32 mStartTicks;

        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};



#endif

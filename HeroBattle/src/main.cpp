#include"Engine.h"
#include <stdlib.h>
#include<ctime>
#include"Timer.h"
#include<iostream>

const float time_slice = 0.01f;
float time_accumulator=0.0f;
float time_last_update = Timer::GetInstance()->getTime();
int main(int argc, char*argv[])
{
    srand(time(0));
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        float deltaTime = Timer::GetInstance()->getTime()- time_last_update;
        time_last_update+=deltaTime;
        time_accumulator+=deltaTime;
        while(time_accumulator>=time_slice)
        {
            time_accumulator-=time_slice;
            Engine::GetInstance()->Events();
            Engine::GetInstance()->Update(deltaTime);
        }
        Engine::GetInstance()->Render();
    }

    Engine::GetInstance()->Clean();
    return 0;
}


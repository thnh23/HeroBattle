#ifndef ENGINE_H
#define ENGINE_H

#include"SDL.h"
#include"SDL_image.h"
#include"GameMap.h"

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

class Engine
{
  public:

  static Engine* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new Engine();
  }
   bool Init();
   void Clean();
   void Quit();

   void Update();
   void Render();
   void Events();
   inline GameMap* GetMap(){return m_LevelMap;}
   inline bool IsRunning(){return m_IsRunning;}
   inline SDL_Renderer* getRenderer(){return m_Renderer;}

  private:
    Engine(){};

    static Engine* m_Instance;
    bool m_IsRunning;
    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
};

#endif

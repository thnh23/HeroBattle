
#ifndef ENGINE_H
#define ENGINE_H

#include"SDL.h"
#include"SDL_image.h"
#include"GameMap.h"
#include"SDL_ttf.h"
#include"GameStateMachine.h"
#include"MapParser.h"
#include "SDL_mixer.h"

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

   void Update(float dt);
   void Render();
   void Events();
   inline GameMap* GetMap(){return m_LevelMap;}
   inline void setMap(std::string id){m_LevelMap= MapParser::GetInstance()->GetMap(id);}
   inline bool IsRunning(){return m_IsRunning;}
   inline SDL_Renderer* getRenderer(){return m_Renderer;}
   inline TTF_Font* getFont(){return m_Font;}
   inline GameStateMachine* getStateMachine() { return gameStateMachine; }
   inline Mix_Music* getMusic(){return m_Music;}

  private:
    Engine(){};
    static Engine* m_Instance;
    bool m_IsRunning;
    GameMap* m_LevelMap;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    TTF_Font* m_Font;
    GameStateMachine* gameStateMachine;
    Mix_Music* m_Music;

};

#endif

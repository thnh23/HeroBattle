#include"Engine.h"
#include"TextureManager.h"
#include"Knight.h"
#include"Input.h"
#include"SDL.h"
#include<iostream>
#include"MapParser.h"
Engine* Engine::m_Instance = nullptr;
Knight* player = nullptr;

bool Engine::Init()
{
  if(SDL_Init(SDL_INIT_VIDEO) !=0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) !=0)
  {
    SDL_Log("Failed to initialize SDL");
    return false;
  }
  m_Window = SDL_CreateWindow("Hero Batlle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
  if(m_Window== nullptr)
  {
    SDL_Log("Failed to creater window");
    return false;
  }
  m_Renderer = SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(m_Renderer ==nullptr)
  {
    SDL_Log("Failed to creater renderer");
    return false;
  }
  if(MapParser::GetInstance()->Load())
  {
      std::cout<<"Failed to load map" <<std::endl;
  }
  m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
  TextureManager::GetInstance()->Load("knight","Image/Idle.png");
  TextureManager::GetInstance()->Load("knight_run","Image/Run.png");
  TextureManager::GetInstance()->Load("knight_jump","Image/Jump.png");
  TextureManager::GetInstance()->Load("knight_defend","Image/Defend.png");
  player = new Knight(new Properties("knight",0,300,72,86));
 return m_IsRunning = true;
}

void Engine::Clean()
{
  TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();


}

void Engine::Quit()
{
  m_IsRunning=false;
}

void Engine::Update()
{
  m_LevelMap->Update();
  player->Update(0.6);
}
void Engine::Render()
{
  SDL_RenderClear(m_Renderer);
 m_LevelMap->Render();
  player->Draw();
  SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
  Input::GetInstance()->Listen();

}

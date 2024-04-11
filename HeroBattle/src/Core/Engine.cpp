#include"Engine.h"
#include"TextureManager.h"
#include"Input.h"
#include<iostream>
#include"MapParser.h"
#include "Camera.h"
#include"GamePlay.h"
#include"HUD.h"
#include"Button.h"
#include"MenuState.h"


Engine* Engine::m_Instance = nullptr;


bool Engine::Init()
{
  if(TTF_Init() !=0)
  {
      return false;
  }
  if(SDL_Init(SDL_INIT_EVERYTHING)<0)
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
  if(MapParser::GetInstance()->Load("Maps/Map.tmx","MAP"))
  {
      std::cout<<"Failed to load map" <<std::endl;
  }
  m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
  m_Font = TTF_OpenFont("Maps/MinimalPixelFont.ttf",20);
  if(m_Font == nullptr)
  {
    SDL_Log("Failed to load font");
    return false;
  }


  TextureManager::GetInstance()->Load("bg","Maps/country-platform-back.png");
  TextureManager::GetInstance()->Load("knight","Image/Idle.png");
  TextureManager::GetInstance()->Load("knight_run","Image/Run.png");
  TextureManager::GetInstance()->Load("knight_jump","Image/Jump1.png");
  TextureManager::GetInstance()->Load("knight_fall","Image/Falling.png");
  TextureManager::GetInstance()->Load("knight_defend","Image/Defend.png");
  TextureManager::GetInstance()->Load("knight_attack1","Image/Attack 1.png");
  TextureManager::GetInstance()->Load("knight_hurt","Image/Hurt.png");
  TextureManager::GetInstance()->Load("enemy","Image/Skeleton_01_White_Idle.png");
  TextureManager::GetInstance()->Load("enemy_run","Image/Skeleton_01_White_Walk.png");
  TextureManager::GetInstance()->Load("enemy_attack","Image/Skeleton_01_White_Attack1.png");
   TextureManager::GetInstance()->Load("enemy_hurt","Image/Skeleton_01_White_Hurt.png");
   TextureManager::GetInstance()->Load("coin","Image/MonedaD.png");
    TextureManager::GetInstance()->Load("playbutton","Image/start.png");
    TextureManager::GetInstance()->Load("inforbutton","Image/information.png");
    TextureManager::GetInstance()->Load("closebutton","Image/close.png");
    TextureManager::GetInstance()->Load("shopbutton","Image/shop.png");
    TextureManager::GetInstance()->Load("settingbutton","Image/setting.png");
    TextureManager::GetInstance()->Load("menu_bg","Maps/Grassy_Mountains_preview_fullcolor.png");
     TextureManager::GetInstance()->Load("resume_border","Image/border_02.png");
     TextureManager::GetInstance()->Load("black_img","Maps/black_image.png");
     TextureManager::GetInstance()->Load("continuebutton","Image/continue.png");
     TextureManager::GetInstance()->Load("homebutton","Image/home.png");
     TextureManager::GetInstance()->Load("restartbutton","Image/restart.png");
  Input::GetInstance()->init();
  HUD::GetInstance()->initHUD();
GamePlay::GetInstance()->init();
    Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
  gameStateMachine = new GameStateMachine();
  gameStateMachine->pushState(new MenuState());

 return m_IsRunning = true;
}

void Engine::Update(float dt)
{
     gameStateMachine->update(dt);
}

void Engine::Render()
{
    SDL_RenderClear(m_Renderer);
     gameStateMachine->render();
  SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
  Input::GetInstance()->Listen();

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

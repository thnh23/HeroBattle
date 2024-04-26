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
#include"GameOverState.h"
#include"GameWin.h"


Engine* Engine::m_Instance = nullptr;


bool Engine::Init()
{
    if(TTF_Init() !=0)
    {
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048) < 0)
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
    MapParser::GetInstance()->Load("Maps/Map1.tmx","MAP1");
    MapParser::GetInstance()->Load("Maps/Map2.tmx","MAP2");
    MapParser::GetInstance()->Load("Maps/Map3.tmx","MAP3");
    MapParser::GetInstance()->Load("Maps/Map4.tmx","MAP4");
     MapParser::GetInstance()->Load("Maps/Map5.tmx","MAP5");



//
    m_Font = TTF_OpenFont("Maps/MinimalPixelFont.ttf",20);
    if(m_Font == nullptr)
    {
        SDL_Log("Failed to load font");
        return false;
    }
    m_Music= Mix_LoadMUS("Maps/Clement Panchout_ Village_ 2002.wav");
    if(m_Music == nullptr)
    {
        return false;
    }
    TextureManager::GetInstance()->Load("bg","Maps/country-platform-back.png");
    //knight
    TextureManager::GetInstance()->Load("knight","Image/Idle.png");
    TextureManager::GetInstance()->Load("knight_run","Image/Run.png");
    TextureManager::GetInstance()->Load("knight_jump","Image/Jump1.png");
    TextureManager::GetInstance()->Load("knight_fall","Image/Falling.png");
    TextureManager::GetInstance()->Load("knight_defend","Image/Defend.png");
    TextureManager::GetInstance()->Load("knight_attack1","Image/Attack 1.png");
    TextureManager::GetInstance()->Load("knight_hurt","Image/Hurt1.png");
    TextureManager::GetInstance()->Load("knight_die","Image/Dead.png");
    TextureManager::GetInstance()->Load("knight_special","Image/crescent_base_form_sheet.png");
    //enemy
    TextureManager::GetInstance()->Load("enemy","Image/Skeleton_01_White_Idle.png");
    TextureManager::GetInstance()->Load("enemy_run","Image/Skeleton_01_White_Walk.png");
    TextureManager::GetInstance()->Load("enemy_attack","Image/Skeleton_01_White_Attack1.png");
    TextureManager::GetInstance()->Load("enemy_hurt","Image/Skeleton_01_White_Hurt.png");
    TextureManager::GetInstance()->Load("enemy_die","Image/Skeleton_01_White_Die.png");
    //boss
    TextureManager::GetInstance()->Load("boss","Image/hooded knight idle.png");
    TextureManager::GetInstance()->Load("boss_attack","Image/hooded knight attack.png");
    TextureManager::GetInstance()->Load("boss_special","Image/hooded knight powerup.png");
    TextureManager::GetInstance()->Load("boss_transition","Image/run-idle transition.png");
    TextureManager::GetInstance()->Load("boss_run","Image/optimusprime.png");
    //coin
    TextureManager::GetInstance()->Load("coin","Image/MonedaD.png");
    //button
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
    TextureManager::GetInstance()->Load("red_poison","Image/redpoison.png");
    TextureManager::GetInstance()->Load("sword","Image/sword.png");
    TextureManager::GetInstance()->Load("shield","Image/shield.png");
    TextureManager::GetInstance()->Load("buy","Image/buy.png");
    TextureManager::GetInstance()->Load("back","Image/back.png");
    TextureManager::GetInstance()->Load("loading","Image/polygon1.png");
     Mix_PlayMusic(m_Music,-1);
      Mix_VolumeMusic(10);
    GamePlay::GetInstance()->init();

    Camera::GetInstance()->SetTarget(GamePlay::GetInstance()->getKnight()->GetOrigin());
    Input::GetInstance()->init();
    HUD::GetInstance()->initHUD();
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
    GamePlay::GetInstance()->close();
    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
    m_LevelMap=nullptr;
    gameStateMachine->popState();
    gameStateMachine=nullptr;
    SDL_DestroyRenderer(m_Renderer);
    m_Renderer=nullptr;
    SDL_DestroyWindow(m_Window);
    m_Window=nullptr;
    Mix_FreeMusic(m_Music);
    m_Music=nullptr;
    TTF_CloseFont(m_Font);
    m_Font=nullptr;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


void Engine::Quit()
{
    m_IsRunning=false;
}


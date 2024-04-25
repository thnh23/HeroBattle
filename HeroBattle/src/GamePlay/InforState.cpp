
#include "InforState.h"
#include"Engine.h"
#include"MenuState.h"
#include"Button.h"

const std::string InforState::inforID = "INFOR";
void InforState::update(float dt)
{
closeInfor->update();
}

void InforState::render()
{
  SDL_Color color{10,200,45};
  TextureManager::GetInstance()->DrawFrameNoCamera("menu_bg",-100,0,1138,640,1,0);
  TextureManager::GetInstance()->Draw("black_img",0,0,1920,1080);
  TextureManager::GetInstance()->DrawAlphaMode("black_img",100);
  closeInfor->draw();

   TextureManager::GetInstance()->DrawFrameNoCamera("resume_border",SCREEN_WIDTH/2-300,SCREEN_HEIGHT/2-300,600,600,1,0);
   TextureManager::GetInstance()->RenderText("INTRODUCTION",{255,255,255},SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2-200,50);
   TextureManager::GetInstance()->RenderText("MOVE LEFT/RIGHT: A/D",{255,255,255},SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-150,50);
   TextureManager::GetInstance()->RenderText("JUMP: W",{255,255,255},SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-100,50);
   TextureManager::GetInstance()->RenderText("ATTACK: J",{255,255,255},SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2-50,50);
   TextureManager::GetInstance()->RenderText("SKILL: K",{255,255,255},SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2,50);
   TextureManager::GetInstance()->RenderText("DEFFEND: S",{255,255,255},SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2+50,50);
    TextureManager::GetInstance()->RenderText("ENJOY THE GAME",{255,255,255},SCREEN_WIDTH/2-100,SCREEN_HEIGHT/2+100,50);

}

bool InforState::onEnter()
{
    closeInfor = new Button("back",SCREEN_WIDTH-100,20,64,32,1);
    return true;
}

bool InforState::onExit()
{
    delete(closeInfor);
    closeInfor=nullptr;

    return true;
}

void InforState::onMouseButtonUp(SDL_Event& e)
{
  if(closeInfor->checkCollision(Input::GetInstance()->getMousePos()))
  {
      Engine::GetInstance()->getStateMachine()->changeState(new MenuState());
  }
}

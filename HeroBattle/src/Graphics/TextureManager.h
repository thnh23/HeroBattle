#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include<string>
#include"SDL.h"
#include<map>
class TextureManager
{
    public:
    static TextureManager* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new TextureManager();
  }
  bool Load(std::string id, std::string fileName);
  void Drop(std::string id);
  void Clean();
  void Draw(std::string id, int x,int y, int width,int height, SDL_RendererFlip flip =SDL_FLIP_NONE);
  void DrawFrame(std::string id, int x,int y, int width,int height, int row,int frame, SDL_RendererFlip flip =SDL_FLIP_NONE);
  void DrawFrameNoCamera(std::string id, int x,int y, int width,int height, int row,int frame, SDL_RendererFlip flip =SDL_FLIP_NONE);
  void DrawTile(std::string tilesetID,int tileSize, int x,int y, int row,int frame, SDL_RendererFlip flip =SDL_FLIP_NONE);
  void RenderText(std::string textureText, SDL_Color textColor, int x, int y, int size);
 void DrawAlphaMode(std::string textureText, Uint8 alpha);

  private:
  TextureManager(){};
  std::map<std::string, SDL_Texture*> m_TextureMap;
  static TextureManager* m_Instance;
};


#endif

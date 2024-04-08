#include"TextureManager.h"
#include"Engine.h"
#include<iostream>
#include"Camera.h"
TextureManager* TextureManager::m_Instance=nullptr;

bool TextureManager::Load(std::string id, std::string fileName)
{
    SDL_Surface* surface =IMG_Load(fileName.c_str());
    if(surface ==  nullptr)
    {
        std::cout<<"Failed to load texture!";
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(),surface);
    if(texture==nullptr)
    {
        std::cout<<"Failed to load texture from surface";
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
     Vector2D cam =Camera::GetInstance()->GetPos();
    SDL_Rect srcRect = {0,0,width,height};
    SDL_Rect dstRect = {(x-cam.X),y-cam.Y,width,height};
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id],&srcRect,&dstRect,0,nullptr,flip );
}

void TextureManager::DrawFrame(std::string id, int x,int y, int width,int height, int row,int frame, SDL_RendererFlip flip )
{
     Vector2D cam =Camera::GetInstance()->GetPos();
    SDL_Rect srcRect ={width*frame,height*(row-1),width,height};
    SDL_Rect dstRect ={x-cam.X,y-cam.Y,width,height};
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[id],&srcRect,&dstRect,0,nullptr,flip );
}
void TextureManager::DrawTile(std::string tilesetID,int tileSize, int x,int y, int row,int frame, SDL_RendererFlip flip)
{
     Vector2D cam =Camera::GetInstance()->GetPos();

     SDL_Rect dstRect ={x- cam.X,y-cam.Y, tileSize, tileSize};
     SDL_Rect srcRect ={tileSize*frame, tileSize*(row), tileSize,tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->getRenderer(),m_TextureMap[tilesetID],&srcRect,&dstRect,0,0,flip );

}
void TextureManager::Drop(std::string id)
{
  SDL_DestroyTexture(m_TextureMap[id]);
  m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string,SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it!= m_TextureMap.end();it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
}


void TextureManager::RenderText(std::string textureText, SDL_Color textColor, int x, int y, int size)
{
	//SDL_RenderClear(Engine::GetInstance()->getRenderer());

	SDL_Surface *textSurface = TTF_RenderText_Solid(Engine::GetInstance()->getFont(), textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), textSurface);

	if (texture == NULL)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << '\n';
		return;
	}


	SDL_FreeSurface(textSurface);

	SDL_Rect textBox{x, y, 0, 0};
	TTF_SetFontSize(Engine::GetInstance()->getFont(), size);
	TTF_SizeText(Engine::GetInstance()->getFont(), textureText.c_str(), &textBox.w, &textBox.h);
	SDL_RenderCopy(Engine::GetInstance()->getRenderer(), texture, NULL, &textBox);
}


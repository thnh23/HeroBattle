#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include"Knight.h"
#include"Enemy.h"
#include<vector>
#include"Vector2D.h"
#include"Item.h"

class GamePlay
{
    public:
     static GamePlay* GetInstance()
  {
    return m_Instance =(m_Instance !=nullptr)?m_Instance : new GamePlay();
  }
   void init();
   void update(float dt);
   void draw();
   Knight* getKnight(){return player;}
   int getNumCoin(){return CoinCount;}
   void setNumCoin(int x){CoinCount=x;}
   void updateCoin(int x){CoinCount-=x;}


    private:
    SDL_Color color{255,255,0};
    int CoinCount;
     static GamePlay* m_Instance;
    Knight* player;
    std::vector<Enemy*> enemyArr ;
    std::vector<Enemy*> enemyAttack;
    std::vector<Item*>  ItemArr;
};

#endif // GAMEPLAY_H

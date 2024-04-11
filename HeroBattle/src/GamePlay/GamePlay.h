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

    private:
    int CoinCount;
     static GamePlay* m_Instance;
    Knight* player;
    std::vector<Enemy*> enemyArr ;
    std::vector<Enemy*> enemyAttack;
    std::vector<Item*>  ItemArr;
};

#endif // GAMEPLAY_H

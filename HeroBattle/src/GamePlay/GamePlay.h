#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include"Knight.h"
#include"Enemy.h"
#include<vector>
#include"Vector2D.h"
#include"Item.h"
#include"Boss.h"

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
   void close();
   Knight* getKnight(){return player;}
   std::vector<Boss*> getBoss(){return bossArr;}
  void addEnemy(int num)
  {
      for(int i=0;i<num;i++)
      {
            enemyArr.push_back(new Enemy(new Properties("enemy",rand()%1800+300,200,96,64)));
      }
  }


   int getNumCoin(){return CoinCount;}
   void setNumCoin(int x){CoinCount=x;}
   void updateCoin(int x){CoinCount-=x;}
   int getEnemyKill(){return EnemyKill;}

    private:
    SDL_Color color{255,255,0};
    int CoinCount;
    int EnemyKill;
     static GamePlay* m_Instance;
    Knight* player;
    std::vector<Enemy*> enemyArr ;
    std::vector<Enemy*> enemyAttack;
   std::vector<Boss*> bossArr;
   std::vector<Boss*> bossAttack;
    std::vector<Item*>  ItemArr;
};

#endif // GAMEPLAY_H

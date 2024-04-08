#ifndef COIN_H
#define COIN_H
#include"Item.h"
class Coin : public Item
{
public:
   Coin(Properties* props);
      virtual void Draw();
      virtual void Update(float dt);
      virtual void Clean();
private:

};

#endif // COIN_H

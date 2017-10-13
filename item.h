#ifndef ITEM_H
# define ITEM_H

# include "util.h"
#include <string>

#ifdef __cplusplus
extern "C++" {
#endif

# include <cstdint>

class item {
public:
  ~item();
  int x;
  int y;
  std::string name;
  std::string description;
  std::string type;
  char symbol;
  int color;
  int hit;
  int damage;
  int dodge;
  int defence;
  int weight;
  int speed;
  int attribute;
  int value;
  int index;
  dice diceHit;
  dice diceDamage;
  dice diceDodge;
  dice diceDefence;
  dice diceWeight;
  dice diceSpeed;
  dice diceAttribute;
  dice diceValue;

  inline item(int x, int y){
    this->x = x;
    this->y = y;
  }


};





#ifdef __cplusplus
}
#endif



#endif

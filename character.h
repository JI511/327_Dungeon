#ifndef CHARACTER_H
# define CHARACTER_H


# include "util.h"
#include <string>

#ifdef __cplusplus
extern "C++" {
#endif

# include <cstdint>

class character {
public:
  character();
  ~character();
  Point_t point;
  uint8_t abilities : 5;
  int speed;
  int turns;
  int alive;
  int index;
  int see;
  char rep;
  int color;
  std::string name;
  std::string description;
  int hitpoints;
  int damage;
  dice diceDamage;


  inline void initialize(int8_t x, int8_t y, int index) {
    this->point.x = x;
    this->point.y = y;
    this->index = index;
  }

  inline character(int8_t x, int8_t y, int index, char rep){
    initialize(x, y, index);
    this->turns = 0;
    this->alive = 1;
    this->see = 0;
    this->rep = rep;
  }
};

class pc : public character{
public:
  char visDun[21][80];
  int radius;

  inline pc(int8_t x, int8_t y, int index) : character(x, y, index, '@'){
    this->speed = 10;
    radius = 3;
    dice di;
    di.set(3,2,8);
    this->hitpoints = 10000;
    this->name = "PLAYER";
    this->diceDamage = di;
    int i,j;
    for(i = 0; i < 21; i++){
      for(j = 0; j < 80; j++){
        visDun[i][j] = ' ';
      }
    }
  }
};

class npc : public character {
public:
  dice diceHitpoints;
  dice diceSpeed;
  //int8_t get4();
  inline npc(int8_t x, int8_t y, int index) : character(x, y, index, ' '){
    //this->speed = (rand() % 15) + 5;
    //this->abilities = get4();
    // char rep;
    // if (this->abilities < 10) {
    //   rep = this->abilities + '0';
    //   //dun[enemies[i].point.y][enemies[i].point.x].type = enemies[i].rep;
    // }
    // else {
    //   rep = this->abilities + 'a' - 10;
    //   //dun[enemies[i].point.y][enemies[i].point.x].type = enemies[i].rep;
    // }
    // this->rep = rep;
    //character(x, y, index, rep);
  }
};




#ifdef __cplusplus
}
#endif



#endif

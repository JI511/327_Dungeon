#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "character.h"
#include "util.h"

Point_t getPoint(enemy_t *enemy){
  return ((character *) enemy)->point;
}
int getX(enemy_t *enemy){
  return ((character *) enemy)->point.x;
}
int getY(enemy_t *enemy){
  return ((character *) enemy)->point.y;
}
void setPoint(enemy_t *enemy, int x, int y){
  ((character *) enemy)->point.x = x;
  ((character *) enemy)->point.y = y;
}
int getAlive(enemy_t *enemy){
  return ((character *) enemy)->alive;
}
void setAlive(enemy_t * enemy, int num){
  ((character *) enemy)->alive = num;
}
int getSpeed(enemy_t *enemy){
  return ((character *) enemy)->speed;
}
void setSpeed(enemy_t *enemy, int speed){
  ((character *) enemy)->speed = speed;
}
uint8_t getAbilities(enemy_t *enemy){
  return ((character *) enemy)->abilities;
}
void setAbilities(enemy_t *enemy, uint8_t abilities){
  ((character *) enemy)->abilities = abilities;
}
int getTurn(enemy_t *enemy){
  return ((character *) enemy)->turns;
}
void setTurn(enemy_t *enemy, int num){
  ((character *) enemy)->turns = num;
}
int getIndex(enemy_t *enemy){
  return ((character *) enemy)->index;
}
void setIndex(enemy_t *enemy, int num){
  ((character *) enemy)->index = num;
}
int getSee(enemy_t *enemy){
  return ((character *) enemy)->see;
}
void setSee(enemy_t *enemy, int num){
  ((character *) enemy)->see = num;
}
char getRep(enemy_t *enemy){
  return ((character *) enemy)->rep;
}
void setRep(enemy_t *enemy, char a){
  ((character *) enemy)->rep = a;
}
int getColor(enemy_t *enemy){
  return ((character *) enemy)->color;
}
void setColor(enemy_t *enemy, int num){
  ((character *) enemy)->color = num;
}
int getHitpoints(enemy_t *enemy){
  return ((character *) enemy)->hitpoints;
}
void setHitpoints(enemy_t *enemy, int num){
  ((character *) enemy)->hitpoints = num;
}
int getDiceDamage(enemy_t *enemy){
  dice di;
  di = ((character *) enemy)->diceDamage;
  return di.roll();
}

void deleteChars(){
  for(uint8_t i = 0; i < enemies.size(); i++){
    delete ((character *) enemies[i]);
  }
}


void printVisDun(){
  pc *playa = (pc *) enemies[0];
  int i,j;
  for(i = playa->point.y - playa->radius; i < playa->point.y + playa->radius; i++){
    for(j = playa->point.x - playa->radius; j < playa->point.x + playa->radius; j++){
      if(i > 0 && i < 20 && j > 0 && j < 79){
        playa->visDun[i][j] = dun[i][j].type;
      }
    }
  }
  clear();
  move(1,0);
  printw("Dungeon Pro Assignment 1.08\n");
  //printw("012345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
  //printw("000000000011111111112222222222333333333344444444445555555555666666666677777777778\n");
  for (int h = 0; h < 21; h++) {
    for (int w = 0; w < 80; w++) {
      if (h >= playa->point.y - playa->radius && h <= playa->point.y + playa->radius && w >= playa->point.x - playa->radius && w <= playa->point.x + playa->radius) {
        attron(A_BOLD);
      }
      printw("%c", playa->visDun[h][w]);
      if (h >= playa->point.y - playa->radius && h <= playa->point.y + playa->radius && w >= playa->point.x - playa->radius && w <= playa->point.x + playa->radius) {
        attroff(A_BOLD);
      }
    }
    printw("\n");
  }
  printw("Name: John Ingwersen  Health: 100    Stamina: 63\n");
  printw("Items:     Room Num: 8\n");
  refresh();
}


character::character(){}
character::~character(){}

void genCharacters(int count){
  int i;
  for(i = 0; i <= count; i++){
    if (i == 0){
      int x = (rand() % dRooms[playerRoom].rWidth) + dRooms[playerRoom].x;
      int y = (rand() % dRooms[playerRoom].rHeight) + dRooms[playerRoom].y;
      enemies.push_back((enemy_t *) new pc(x,y,0));
      dun[y][x].type = getRep(enemies[i]);
      setColor(enemies[0], 4);
      init_pair(getColor(enemies[0]), getColor(enemies[0]), COLOR_BLACK);
    }
    else {
      int r = rand() % sizeof(dRooms);
        while (r==playerRoom){
          r = rand() % sizeof(dRooms);
        }
      int x = (rand() % dRooms[r].rWidth) + dRooms[r].x;
      int y = (rand() % dRooms[r].rHeight) + dRooms[r].y;
      enemies[i] = (enemy_t *) new npc(x,y,i);
      dun[y][x].type = getRep(enemies[i]);
    }
  }

}

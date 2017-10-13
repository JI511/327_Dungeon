#ifndef UTIL_H
# define UTIL_H

#include <vector>
#include "descriptions.h"
#include "dice.h"
#include "item.h"
#include <map>

typedef struct hello {
  std::vector<monster_description> monster_descriptions;
  std::vector<object_description> object_descriptions;
} hello_t;

# ifdef __cplusplus
extern "C" {
# endif


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
//#include <endian.h>
#include "../portable_endian.h"
#include "playDungeon.h"
#include "heap.h"



# define NPC_INTEL 0x0001 //if intelligent
# define NPC_TELEP 0x0002 // if telepathic
# define NPC_IFTUN 0x0004 //if tunnel
# define NPC_ERRAT 0x0008 //is erratic
# define NPC_PASS  0x0010 //can pass

#define SAVE_DIR               ".rlg327"
#define DUNGEON_SAVE_FILE      "dungeon"
#define DUNGEON_SAVE_SEMANTIC  "RLG327"
#define DUNGEON_SAVE_VERSION   0U
#define MONSTER_DESC_FILE      "monster_desc.txt"
#define OBJECT_DESC_FILE       "object_desc.txt"

# define rand_range(min, max) ((rand() % (((max) + 1) - (min))) + (min))


int checkCollision(int num, int y, int x);
void toString();
int8_t get4();
void drawPlayer();
int roomGen(int count);
void lineGen(int i);
void drawMonsters(int count);
void drawStairs();
void initialize();
int checkRoom(int num);


typedef struct Point {
  int x;
  int y;
} Point_t;



typedef struct center {
  int x;
  int y;
} center_t;

//xy starting at the top left corner of room
typedef struct rooms {
  int x;
  int y;
  int rHeight;
  int rWidth;
} room_t;


typedef struct dungeon {
  int hardness;
  char type;
  int ifRoom;
  int isStair;
  int hasItem;
  char item;
  int itemIndex;
} dungeon_t;


typedef struct dist {
  heap_node_t *hn;
  int distance;
  Point_t point;
} dist_t;


typedef struct enemy {
  char ipreferjava;
} enemy_t;




extern hello_t descriptions;
extern dungeon_t dun[21][80];
extern dist_t distance[21][80];
extern std::vector<enemy_t *> enemies;
extern std::vector<item *> items;
extern std::map<std::string, item *> equipment;
extern std::vector<item *> inventory;
extern room_t *dRooms;
extern int monsterCount;
extern int itemCount;
extern int roomNum;
extern int playerRoom;
Point_t getPoint(enemy_t *enemy);
void setPoint(enemy_t *enemy, int x, int y);
int getAlive(enemy_t *enemy);
void setAlive(enemy_t * enemy, int num);
int getSpeed(enemy_t *enemy);
void setSpeed(enemy_t *enemy, int speed);
uint8_t getAbilities(enemy_t *enemy);
void setAbilities(enemy_t *enemy, uint8_t abilities);
int getTurn(enemy_t *enemy);
void setTurn(enemy_t *enemy, int num);
int getIndex(enemy_t *enemy);
void setIndex(enemy_t *enemy, int num);
int getSee(enemy_t *enemy);
void setSee(enemy_t *enemy, int num);
char getRep(enemy_t *enemy);
void setRep(enemy_t *enemy, char a);
int getX(enemy_t *enemy);
int getY(enemy_t *enemy);
int getColor(enemy_t *enemy);
void setHitpoints(enemy_t *enemy, int num);
int getHitpoints(enemy_t *enemy);
void genCharacters(int count);
void printVisDun();
void deleteChars();
void pathFinder(Point_t p, int isTun);
int parseMon();
void deleteItems();
void drawItems(int count);
int getDiceDamage(enemy_t *);


# ifdef __cplusplus
}
# endif

#endif

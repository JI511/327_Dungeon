
#include "util.h"
#include "character.h"
#include "descriptions.h"
#include "item.h"
#include <vector>
#include <map>

int roomNum = 8;
char *path;
int monsterCount = 3;
int itemCount = 10;
int playerRoom;
center_t centerA[8];
room_t *dRooms;
hello_t descriptions;
dungeon_t dun[21][80];
dist_t distance[21][80];
std::vector<enemy_t *> enemies;
std::vector<item *> items;
std::map<std::string, item *> equipment;
std::vector<item *> inventory;


void toString() {
  clear();
  move(1,0);
  printw("Dungeon Pro Assignment 1.09\n");
  //printw("012345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
  //printw("000000000011111111112222222222333333333344444444445555555555666666666677777777778\n");
  for (int h = 0; h < 21; h++) {
    for (int w = 0; w < 80; w++) {
      if (dun[h][w].hasItem && dun[h][w].type == '.'){
        attron(COLOR_PAIR(items[dun[h][w].itemIndex]->color));
        printw("%c", dun[h][w].item);
        attroff(COLOR_PAIR(items[dun[h][w].itemIndex]->color));
      }
      else if(dun[h][w].type != '.' && dun[h][w].type != '#' && dun[h][w].type != ' ' && dun[h][w].type != '<' && dun[h][w].type != '>' && dun[h][w].type != '@'){
        for(int k = 1; k <= monsterCount; k++){
          if(getX(enemies[k]) == w && getY(enemies[k]) == h){
            attron(COLOR_PAIR(getColor(enemies[k])));
            printw("%c", dun[h][w].type);
            attroff(COLOR_PAIR(getColor(enemies[k])));
          }
        }
      }
      else {
        printw("%c", dun[h][w].type);
      }

    }
    printw("\n");
  }
  printw("Name: John Ingwersen  Health: %d    Stamina: 63\n", getHitpoints(enemies[0]));
  printw("Items:     Room Num: 8\n");
  refresh();
}

void equipmentSetup() {
  equipment.insert(std::pair<std::string, item *>("WEAPON", NULL));
  equipment.insert(std::pair<std::string, item *>("OFFHAND", NULL));
  equipment.insert(std::pair<std::string, item *>("RANGED", NULL));
  equipment.insert(std::pair<std::string, item *>("ARMOR", NULL));
  equipment.insert(std::pair<std::string, item *>("HELMET", NULL));
  equipment.insert(std::pair<std::string, item *>("CLOAK", NULL));
  equipment.insert(std::pair<std::string, item *>("GLOVES", NULL));
  equipment.insert(std::pair<std::string, item *>("BOOTS", NULL));
  equipment.insert(std::pair<std::string, item *>("AMULET", NULL));
  equipment.insert(std::pair<std::string, item *>("LIGHT", NULL));
  equipment.insert(std::pair<std::string, item *>("RING-L", NULL));
  equipment.insert(std::pair<std::string, item *>("RING-R", NULL));
}

void pickUpItem(){
  if(dun[getY(enemies[0])][getX(enemies[0])].hasItem && inventory.size() < 10){
    items[dun[getY(enemies[0])][getX(enemies[0])].itemIndex]->index = dun[getY(enemies[0])][getX(enemies[0])].itemIndex;
    inventory.push_back(items[dun[getY(enemies[0])][getX(enemies[0])].itemIndex]);
    dun[getY(enemies[0])][getX(enemies[0])].hasItem = 0;
  }
}

void io_init_terminal(void)
    {
      initscr();
      cbreak();
      noecho();
      curs_set(0);
      keypad(stdscr, TRUE);
      start_color();
    }

void drawPlayer() {
  playerRoom = rand() % sizeof(dRooms);
  // enemies[0].point.x = (rand() % dRooms[playerRoom].rWidth) + dRooms[playerRoom].x;
  // enemies[0].point.y = (rand() % dRooms[playerRoom].rHeight) + dRooms[playerRoom].y;
  // enemies[0].speed = 10;
  // enemies[0].alive = 1;
  // enemies[0].turns = 0;
  // // enemies[0].kind = 1;
  // enemies[0].rep = '@';
  // //printw("%d %d %d\n", roomSelect, point.x, point.y);
  // dun[enemies[0].point.y][enemies[0].point.x].type = enemies[0].rep;
}

int8_t get4() {
  int8_t num = 0;
  num = num | rand() % 2;
  num = num | (rand() % 2) * 2;
  num = num | (rand() % 2) * 4;
  num = num | (rand() % 2) * 8;
  //set to test, not Random
  // num = num | 1; //intelligent
  // num = num | 0 * 2; //telepathy
  // num = num | 1 * 4; //tunneling
  // num = num | 0 * 8; //erratic

  return num;
}

int doMove(int y, int x) {
  // if (dun[enemies[0].point.y+y][enemies[0].point.x+x].hardness != 255) {
  //   if (dun[enemies[0].point.y+y][enemies[0].point.x+x].type != '#' && dun[enemies[0].point.y+y][enemies[0].point.x+x].type != '.' && dun[enemies[0].point.y+y][enemies[0].point.x+x].type != ' '){
  //     checkCollision(0, enemies[0].point.y+y, enemies[0].point.x+x);
  //   }
  //   dun[enemies[0].point.y+y][enemies[0].point.x+x].type = '@';
  //   dun[enemies[0].point.y+y][enemies[0].point.x+x].hardness = 0;
  //   if (dun[enemies[0].point.y][enemies[0].point.x].ifRoom == 0) {
  //     dun[enemies[0].point.y][enemies[0].point.x].type = '#';
  //     dun[enemies[0].point.y][enemies[0].point.x].hardness = 0;
  //   }
  //   else {
  //     dun[enemies[0].point.y][enemies[0].point.x].type = '.';
  //     dun[enemies[0].point.y][enemies[0].point.x].hardness = 0;
  //   }
  //   enemies[0].point.y += y;
  //   enemies[0].point.x += x;
  //   return 1;
  // }
  // return 0;
  return 0;
}

void movePlayer() {

  int move = 0;
  while (move == 0) {
    int dir = rand() % 4;
    //int dir = 3;
    switch (dir) {
      case 0:
      //up
        move = doMove(-1, 0);
        break;
      case 1:
      //down
        move = doMove(1, 0);
        break;
      case 2:
      //right
        move = doMove(0, 1);
        break;
      case 3:
      //left
        move = doMove(0, -1);
        break;
    }
  }
}

void drawStairs() {
  for(int i = 0; i < 2; i++){
    int r = rand() % sizeof(dRooms);
    int s = rand() % 2;
    int x = (rand() % dRooms[r].rWidth) + dRooms[r].x;
    int y = (rand() % dRooms[r].rHeight) + dRooms[r].y;
    if(dun[y][x].type < 47){
      if(s){
        dun[y][x].type = '>';
        dun[y][x].isStair = 1;
        dun[y][x].hardness = 0;
      }
      else{
        dun[y][x].type = '<';
        dun[y][x].isStair = 2;
        dun[y][x].hardness = 0;
      }
    }
  }

}

void drawMonsters(int count) {
  for(int i = 1; i <= count; i++){
    dice di;
    int w = rand() % descriptions.monster_descriptions.size();
    int r = rand() % sizeof(dRooms);
    while (r==playerRoom){
      r = rand() % sizeof(dRooms);
    }
    int x = (rand() % dRooms[r].rWidth) + dRooms[r].x;
    int y = (rand() % dRooms[r].rHeight) + dRooms[r].y;
    npc *n = new npc(x,y,i);
    n->diceSpeed = descriptions.monster_descriptions[w].speed;
    di.set(descriptions.monster_descriptions[w].speed.base, descriptions.monster_descriptions[w].speed.number, descriptions.monster_descriptions[w].speed.sides);
    n->speed = di.roll();
    n->abilities = descriptions.monster_descriptions[w].abilities;
    n->diceHitpoints = descriptions.monster_descriptions[w].hitpoints;
    di.set(descriptions.monster_descriptions[w].hitpoints.base, descriptions.monster_descriptions[w].hitpoints.number, descriptions.monster_descriptions[w].hitpoints.sides);
    n->hitpoints = di.roll();
    n->diceDamage = descriptions.monster_descriptions[w].damage;
    n->rep = descriptions.monster_descriptions[w].symbol;
    n->color = descriptions.monster_descriptions[w].color;
    init_pair(n->color, n->color, COLOR_BLACK);
    n->description = descriptions.monster_descriptions[w].description;
    n->name = descriptions.monster_descriptions[w].name;
    enemies.push_back((enemy_t *) n);
    dun[y][x].type = getRep((enemy_t *) n);
  }
}

void drawItems(int count) {
  for(int j = 0; j < count; j++){
    dice di;
    int w = rand() % descriptions.object_descriptions.size();
    int r = rand() % sizeof(dRooms);
    int x = (rand() % dRooms[r].rWidth) + dRooms[r].x;
    int y = (rand() % dRooms[r].rHeight) + dRooms[r].y;
    item *i = new item(x,y);
    i->name = descriptions.object_descriptions[w].name;
    i->description = descriptions.object_descriptions[w].description;
    i->symbol = object_symbol[descriptions.object_descriptions[w].type];
    i->type = types_lookup[descriptions.object_descriptions[w].type].name;
    i->color = descriptions.object_descriptions[w].color;
    init_pair(i->color, i->color, COLOR_BLACK);
    i->diceHit = descriptions.object_descriptions[w].hit;
    di.set(descriptions.object_descriptions[w].hit.base, descriptions.object_descriptions[w].hit.number, descriptions.object_descriptions[w].hit.sides);
    i->hit = di.roll();
    i->diceDamage = descriptions.object_descriptions[w].damage;
    di.set(descriptions.object_descriptions[w].damage.base, descriptions.object_descriptions[w].damage.number, descriptions.object_descriptions[w].damage.sides);
    i->damage = di.roll();
    i->diceDodge = descriptions.object_descriptions[w].dodge;
    di.set(descriptions.object_descriptions[w].dodge.base, descriptions.object_descriptions[w].dodge.number, descriptions.object_descriptions[w].dodge.sides);
    i->dodge = di.roll();
    i->diceDefence = descriptions.object_descriptions[w].defence;
    di.set(descriptions.object_descriptions[w].defence.base, descriptions.object_descriptions[w].defence.number, descriptions.object_descriptions[w].defence.sides);
    i->defence = di.roll();
    i->diceWeight = descriptions.object_descriptions[w].weight;
    di.set(descriptions.object_descriptions[w].weight.base, descriptions.object_descriptions[w].weight.number, descriptions.object_descriptions[w].weight.sides);
    i->weight = di.roll();
    i->diceSpeed = descriptions.object_descriptions[w].speed;
    di.set(descriptions.object_descriptions[w].speed.base, descriptions.object_descriptions[w].speed.number, descriptions.object_descriptions[w].speed.sides);
    i->speed = di.roll();
    i->diceAttribute = descriptions.object_descriptions[w].attribute;
    di.set(descriptions.object_descriptions[w].attribute.base, descriptions.object_descriptions[w].attribute.number, descriptions.object_descriptions[w].attribute.sides);
    i->attribute = di.roll();
    i->diceValue = descriptions.object_descriptions[w].value;
    di.set(descriptions.object_descriptions[w].value.base, descriptions.object_descriptions[w].value.number, descriptions.object_descriptions[w].value.sides);
    i->value = di.roll();
    items.push_back(i);
    dun[y][x].hasItem = 1;
    dun[y][x].item = i->symbol;
    dun[y][x].itemIndex = j;
  }
}

void initialize() {
  for (int h = 0; h < 21; h++) {
    for (int w = 0; w < 80; w++) {
      if (h == 0 || h == 20) {
        dun[h][w].type = ' ';
        dun[h][w].hardness = 255;


      }
      else if (w == 0 || w == 79) {
        dun[h][w].type = ' ';
        dun[h][w].hardness = 255;

      }
      else {
        dun[h][w].type = ' ';
        dun[h][w].hardness = (rand() % 245) + 5;

      }
      dun[h][w].ifRoom = 0;
      dun[h][w].hasItem = 0;
      dun[h][w].isStair = 0;
    }
  }
}
//int count so the function can return a 1 if a room is placed, or a zero if it fails
int roomGen(int count) {


  int height = rand() % 10;
  int width = rand() % 10;
  if (height < 4) {
    height = 4;
  }
  if (width < 4) {
        width = 4;
  }
  //at this point height and width of room are given by previous vars
  //find a location to place the room, search that area to see if its valid
  int modValHeight = 18 - height;
  int modValWidth = 77 - width;
  //corner heights referring to top left corner value within the array
  int cornerStartHeight = rand() % modValHeight;
  int cornerStartWidth = rand() % modValWidth;

  //++ used to make it align with the main array
  cornerStartHeight++;
  cornerStartWidth++;


  int h;
  int w;

  for (h = -1; h < height+1; h++) {
    for (w = -1; w < width+1; w++) {
      if (dun[cornerStartHeight+h][cornerStartWidth+w].type == '.') {
        return 0;
      }
    }
  }

  for (h = 0; h < height; h++) {
    for (w = 0; w < width; w++) {
      dun[cornerStartHeight+h][cornerStartWidth+w].type = '.';
      dun[cornerStartHeight+h][cornerStartWidth+w].hardness = 0;
      dun[cornerStartHeight+h][cornerStartWidth+w].ifRoom = 1;

    }
  }


  //store height in y coord, width in x coord of struct
  centerA[count].y = cornerStartHeight + (height / 2);
  centerA[count].x = cornerStartWidth + (width / 2);
  dRooms[count].x = cornerStartWidth;
  dRooms[count].y = cornerStartHeight;
  dRooms[count].rHeight = height;
  dRooms[count].rWidth = width;



  return 1;

}

void lineGen(int i) {
  int next = i + 1;
  if (i == 7) {
    next = 0;
  }
  //location to store the current position of walls being updated, until the next point is reached
  center_t loc;
  loc.x = centerA[i].x;
  loc.y = centerA[i].y;
  //up and right are boolean, 0 false 1 true, if 0 it is the opposite direction of the name
  int up = 0;
  int right = 0;

  if (centerA[i].y < centerA[next].y) {
    up = 1;
  }
  if (centerA[i].x < centerA[next].x) {
    right = 1;
  }


  int vertical = centerA[i].y - centerA[next].y;
  int horizontal = centerA[next].x - centerA[i].x;


  while (!(vertical == 0 && horizontal == 0)) {

    int moveY = vertical % 3;
    if (vertical % 3 == 0) {
      moveY = vertical / 3;
    }
    int moveX = horizontal % 3;
    if (horizontal % 3 == 0) {
      moveX = horizontal / 3;
    }

    //y direction
    for (int h = 1; h <= abs(moveY); h++) {
      if (up == 0 && vertical != 0) {
        loc.y--;
        if (dun[loc.y][loc.x].type != '.') {
          dun[loc.y][loc.x].type = '#';
          dun[loc.y][loc.x].hardness = 0;

        }
        vertical--;
      }
      if (up == 1 && vertical != 0) {
        loc.y++;
        if (dun[loc.y][loc.x].type != '.') {
          dun[loc.y][loc.x].type = '#';
          dun[loc.y][loc.x].hardness = 0;

        }
        vertical++;
      }
    }
    //x direction
    for (int w = 1; w <= abs(moveX); w++) {
      if (right == 0 && horizontal != 0) {
        loc.x--;
        if (dun[loc.y][loc.x].type != '.') {
          dun[loc.y][loc.x].type = '#';
          dun[loc.y][loc.x].hardness = 0;
        }
        horizontal++;
      }
      if (right == 1 && horizontal != 0) {
        loc.x++;
        if (dun[loc.y][loc.x].type != '.') {
          dun[loc.y][loc.x].type = '#';
          dun[loc.y][loc.x].hardness = 0;
        }
        horizontal--;
      }
    }


  }


}

void load() {
  FILE *file = fopen(path, "rb");
  //printw("%s\n", path);
  //first 6 bytes are name
  char *name = (char *) malloc(sizeof(*name) * 7);
  //version is next 4
  uint32_t version = 0;
  uint32_t fSize = 0;
  fread(name, sizeof(*name), 6, file);
  fread(&version, sizeof(version), 1, file);
  fread(&fSize, sizeof(fSize), 1, file);
  fSize = htobe32(fSize);
  strcat(path, "\0");
  //printw("path %s\n", path);
  //printw("version %d\n", version);
  //printw("size %d\n", fSize);
  int r;
  int c;
  for(r = 1; r < 20; r++) {
    for(c = 1; c < 79; c++) {
      char spot;
      fread(&spot, sizeof(spot), 1, file);
      dun[r][c].hardness = (int) spot;
      if (dun[r][c].hardness == 0) {
        dun[r][c].type = '#';
      }
      else {
        dun[r][c].type = ' ';
      }

    }
  }

  int remaining = fSize - 1496;
  //printw("SIZE %d REMAIN %d\n", fSize, remaining);
  roomNum = remaining / 4;
  dRooms = (room_t *) malloc(sizeof(*dRooms) * roomNum);
  //printw("remaining %d\n", remaining);
  for (int i = 0; i < roomNum; i++){
    char xPos, yPos, hei, wid;
    fread(&xPos, sizeof(xPos), 1, file);
    fread(&yPos, sizeof(yPos), 1, file);
    fread(&wid, sizeof(wid), 1, file);
    fread(&hei, sizeof(hei), 1, file);

    int x = (int) xPos;
    int xT = x;
    int y = (int) yPos;
    //int yT = y;
    int wi = (int) wid;
    int he = (int) hei;

    dRooms[i].x = x;
    dRooms[i].y = y;
    dRooms[i].rWidth = wi;
    dRooms[i].rHeight = he;

    //printw("x %d y %d hi %d wi %d\n", x, y, he, wi);
    for (r = 0; r < he; r++) {
      for (c = 0; c < wi; c++) {
        dun[y][x].type = '.';
        dun[y][x].hardness = 0;
        x++;
      }
      x = xT;
      y++;
    }

  }
  //printw("END OF LOAD\n");
  //toString();
  free(name);
  fclose(file);
}

void save () {
  FILE *file = fopen(path, "wb");
  char *name = (char *) malloc(sizeof(*name) * 7);
  name = (char *) "RLG327";
  fwrite(name, sizeof(*name), 6, file);
  uint32_t version = 0;
  uint32_t fSize = 1496 + (4 * roomNum);
  fwrite(&version, sizeof(version), 1, file);
  fSize = be32toh(fSize);
  fwrite(&fSize, sizeof(fSize), 1, file);

  int r;
  int c;
  for(r = 1; r < 20; r++) {
    for(c = 1; c < 79; c++) {
      char spot = (char) dun[r][c].hardness;
      fwrite(&spot, sizeof(spot), 1, file);

    }
  }

  //int remaining = roomNum * 4;
  //printw("num rooms %d\n", roomNum);
  for (int i = 0; i < roomNum; i++){
    int xPos = dRooms[i].x;
    int yPos = dRooms[i].y;
    int wid = dRooms[i].rWidth;
    int hei = dRooms[i].rHeight;


    //printw("INTS %d %d %d %d\n", xPos, yPos, hei, wid);

    char x = (char) xPos;
    char y = (char) yPos;
    char wi = (char) wid;
    char he = (char) hei;


    //printw("CHARS %c %c %c %c\n", x, y, he, wi);

    fwrite(&x, sizeof(x), 1, file);
    fwrite(&y, sizeof(y), 1, file);
    fwrite(&wi, sizeof(wi), 1, file);
    fwrite(&he, sizeof(he), 1, file);


  }
  fclose(file);
  //printw("END OF SAVE\n");
  //toString();
}

void deleteItems(){
  for(uint8_t i = 0; i < items.size(); i++){
    delete items[i];
  }
}

void deleteInventory(){
  for(uint8_t i = 0; i < inventory.size(); i++){
    delete inventory[i];
  }
}

void deleteEquipment(){
  equipment.clear();
}

int32_t runCompare(const void *key, const void *with) {
  int k = getTurn(((enemy_t *) key));
  int w = getTurn(((enemy_t *) with));
  //return ((enemy_t *) key)->turns - ((enemy_t *) with)->turns;
  return k - w;
}

int main(int argc, char *argv[]) {
  //usleep(9000000);
  io_init_terminal();
  srand(time(NULL));
  equipmentSetup();
  //path = getenv("HOME");
  //strcat(path, "/.rlg327/dungeon.rlg327");
  //strcat(path, "/.rlg327/monster_desc.txt");
  //initialize empty dungeon
  initialize();
  // int val = getch();
  // while (val!=10){
  //   val = getch();
  //   //refresh();
  // }
  //usleep(9000000);



  if (argc == 2) {
    if (strcmp("--load", argv[1]) == 0) {
      load();
      //enemies = (enemy_t **) malloc(sizeof(*enemies) * (monsterCount + 1));
      drawPlayer();
      genCharacters(monsterCount);
      drawStairs();
      printVisDun();
      //toString();
      usleep(5000000);
      //free(enemies);
      free(dRooms);
      endwin();
      return 0;
    }
  }
  if (argc == 3) {
    //printw("if\n");
    //printw("%s %s\n", argv[1], argv[2]);
    if (strcmp("--load", argv[1]) == 0 && strcmp("--save", argv[2]) == 0) {
      //printw("FIRST\n");
      load();
      drawPlayer();
      save();
      //printw("IN METHOD");
      printVisDun();
      //toString();
      return 0;
    }
    if (strcmp("--save", argv[1]) == 0 && strcmp("--load", argv[2]) == 0) {
      //printw("SEC\n");
      load();
      drawPlayer();
      save();
      //printw("IN METHOD");
      printVisDun();
      //toString();
      return 0;
    }
    if (strcmp("--nummon", argv[1]) == 0){
      char *ptr;
      long ret = strtol(argv[2], &ptr, 10);
      monsterCount = (int) ret;
    }
  }
  //malloc it to the preset if load is not being done
  dRooms = (room_t *) malloc(sizeof(*dRooms) * roomNum);
  //generate rooms
  int count = 0;
  while (count < 8) {
    count = count + roomGen(count);
  }
  //create lines between rooms
  for (int i = 0; i < 7; i++) {
    lineGen(i);
  }
  // int val = getch();
  // while (val!=10){
  //   val = getch();
  //   //refresh();
  // }

  drawPlayer();
  //creates only the PC
  genCharacters(0);
  //loads in monsters
  parse_descriptions(&descriptions);
  //create monsters off of descriptions and monsterCount
  drawMonsters(monsterCount);

  drawStairs();

  drawItems(itemCount);

  toString();
  //printVisDun();

  heap_t runHeap;
  heap_init(&runHeap, runCompare, NULL);
  for(int z = 0; z <= monsterCount; z++) {
    heap_insert(&runHeap, enemies[z]);
  }
  enemy_t *e;
  while ((e = (enemy_t *) heap_remove_min(&runHeap))){
    // printw("%d %d %d\n", getIndex(e), getY(e), getX(e));
    // refresh();
    // usleep(5000000);
    if (getIndex(e) == 0) {
      if (getAlive(e) == 0) {
        toString();
        //printVisDun();
        printw("\n\n\n\nYOU LOSE!\n\n\n\n\n");
        refresh();
        usleep(2000000);
        heap_delete(&runHeap);
        break;
      }
      if(getMove() == 1){
        //save();
        deleteChars();
        deleteInventory();
        deleteEquipment();
        deleteItems();
        //free(enemies);
        free(dRooms);
        endwin();
        return 0;
      }
      pickUpItem();
      //movePlayer();
      toString();
      //printVisDun();
      //usleep(500000);
    }
    else if(getAlive(e) == 1) {
      if (getAbilities(e) & NPC_ERRAT) {
        if (erraticMove(getIndex(e)) == 1){
          //move is done, it did erratic behavior
        }
        else{
          //continue normally
          if (getAbilities(e) & NPC_INTEL) {
            //intel and erratic
            if (getAbilities(e) & NPC_TELEP) {
              //smart and telep and erratic
              smartMove(getIndex(e));
            }
            else{
              //erratic and intel, only go after if in same room
              if (checkRoom(getIndex(e)) == 1 || getSee(e) == 1) {
                smartMove(getIndex(e));
              }
              else {
                //dont move, not in same room
              }
            }
          }
          else {
            //erratic
            if(getAbilities(e) & NPC_TELEP) {
              //erratic and telep
              generalMove(getIndex(e));
            }
            else {
              if (checkRoom(getIndex(e)) == 1 || getSee(e) == 1){
                generalMove(getIndex(e));
              }
            }
          }
        }
      }
      else {
        //can only be non erratic behavior here
        if (getAbilities(e) & NPC_INTEL) {
          if (getAbilities(e) & NPC_TELEP) {
            //smart and telep move
            smartMove(getIndex(e));
          }
          else{
            if (checkRoom(getIndex(e)) == 1 || getSee(e) == 1) {
              //is intelligent, but must be in the same room or have seen the player
              smartMove(getIndex(e));
            }
          }
        }
        else {
          //erratic
          if(getAbilities(e) & NPC_TELEP) {
            //telepathic not intelligent, general move toward player
            generalMove(getIndex(e));
          }
          else {
            if (checkRoom(getIndex(e)) == 1 || getSee(e) == 1){
              //has no abilities, however in the same room so it can attack
              generalMove(getIndex(e));
            }
            //dont move, it didnt go erratic and has no other abilities, best to just stay put.
          }
        }
      }
    }
    //e->turns = 100/e->speed + e->turns;
    setTurn(e, (100/getSpeed(e) + getTurn(e)));
    int end = 0;
    for (int t = 1; t <= monsterCount; t++) {
      if (getAlive(enemies[t]) == 1) {
        end = 1;
      }
    }
    if (end == 0) {
      toString();
      //printVisDun();
      printw("\n\n\n\nYOU WIN!!!!\n\n\n\n");
      refresh();
      usleep(2000000);
      heap_delete(&runHeap);
      break;
    }
    if (getAlive(e) == 1) {
      heap_insert(&runHeap, e);
    }
  }

  if (argc == 2) {
    if (strcmp("--save", argv[1]) == 0) {
      save();
      deleteChars();
      //free(enemies);
      free(dRooms);
      endwin();
      return 0;
    }
  }
  endwin();
  deleteChars();
  deleteItems();
  deleteInventory();
  deleteEquipment();
  //free(enemies);
  free(dRooms);
  return 0;
}

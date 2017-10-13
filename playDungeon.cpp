#include "util.h"
//#include "dice.h"

int checkCollision(int num, int y, int x) {
  //printf("COLLISION\nCOLLISION\nCOLLISION\nCOLLISION\nCOLLISION\n");
  for(int i = 0; i <= monsterCount; i++) {
    if(num == 0 && i == 0){
      continue;
    }
    if ((getY(enemies[i]) == y && getX(enemies[i]) == x && getRep(enemies[i]) == '@') || getRep(enemies[num]) == '@') {
      int damage = getDiceDamage(enemies[num]);
      if(num == 0){
        for (auto& x : equipment){
          if(equipment[x.first] != NULL){
            damage += x.second->diceDamage.roll();
            setSpeed(enemies[0], (getSpeed(enemies[0]) + x.second->diceSpeed.roll()));
          }
        }
      }
      int hitpoints = getHitpoints(enemies[i]);
      if(hitpoints > damage){
        //take damage
        setHitpoints(enemies[i], hitpoints-damage);
        return 0;
      }
      else{
        //killed
        setAlive(enemies[i], 0);
        dun[y][x].type = getRep(enemies[num]);
        return 1;
      }
    }

  }
  return 0;

}

void showMonsters(){
  //printw("%d\n", monsterCount);

  int i;
  int index = 1;
  while (1){
    clear();
    move(0,0);
    for(i = index; i <= monsterCount && i < index + 24; i++){
      if (getAlive(enemies[i]) == 1) {
        int h = getY(enemies[i]) - getY(enemies[0]);
        int w = getX(enemies[i]) - getX(enemies[0]);
        if (h >= 0) {
          char *he = (char *) "north";
          if (w >= 0) {
            char *ve = (char *) "west";
            //printw("1 %c %d %d %s\n", enemies[i].rep, h, w, *ve);
            printw("%d: %c, %d %s, %d %s\n", i, getRep(enemies[i]), h, he, w, ve);
          }
          else{
            char *ve = (char *) "east";
            w = abs(w);
            //printw("2 %c %d %d %s\n", enemies[i].rep, h, w, ve);
            printw("%d: %c, %d %s, %d %s\n", i, getRep(enemies[i]), h, he, w, ve);
          }
        }
        else {
          char *he = (char *) "south";
          h = abs(h);
          if (w >= 0) {
            char *ve = (char *) "west";
            //printw("3 %c %d %d\n", enemies[i].rep, h , w);
            printw("%d: %c, %d %s, %d %s\n", i, getRep(enemies[i]), h, he, w, ve);
          }
          else{
            char *ve = (char *) "east";
            w = abs(w);
            //printw("4 %c %d %d\n", enemies[i].rep, h, w);
            printw("%d: %c, %d %s, %d %s\n", i, getRep(enemies[i]), h, he, w, ve);
          }
        }
        refresh();
      }
    }
    int ch = getch();
    if(ch == 27){
      break;
    }
    if(ch == KEY_UP){
      if (index <= monsterCount - 1 && index > 0){
        index++;
      }
    }
    else if(ch == KEY_DOWN){
      if (index <= monsterCount && index > 1){
        index--;
      }
    }

  }
}

void getNew(){
  /*re initialize dungeon rooms and corridors
    keep same enemies, but give new positions
    draw player randomly.
  */
  clear();
  initialize();
  int count = 0;
  int num = 0;
  while (count < 8) {
    count = count + roomGen(count);
  }
  //create lines between rooms
  for (int i = 0; i < 7; i++) {
    lineGen(i);
  }
  for(int j = 1; j <= monsterCount; j++){
    if (getAlive(enemies[j]) == 1){
      num++;
    }
  }
  monsterCount = num;
  //drawPlayer();
  //re place monsters.
  deleteChars();
  deleteItems();
  drawPlayer();
  genCharacters(0);
  drawMonsters(monsterCount);
  drawItems(itemCount);


  //deleteChars();


  //genCharacters(monsterCount);

  drawStairs();
  refresh();
}

void displayInventory(int num){
  uint8_t i, j;
  for(i = 0; i < 12; i++){
    move(5+i, 20);
    for(j = 0; j < 40; j++){
      if(i == 0 || i == 11 || j == 0 || j == 39){
        printw("*");
      }
      else{
        printw(" ");
      }
    }
    //printw("\n");
  }
  move(5,35);
  printw("INVENTORY");
  for(i = 0; i < 10; i++){
    move(6+i,21);
    if(i < inventory.size()){
      printw("Slot %d: %s", i, inventory[i]->name.c_str());
    }
    else{
      printw("Slot %d: %s", i, "NULL");
    }
  }

  refresh();
  while(1){
    int a = getch();
    switch (a) {
      case 48:
      //0
        //wear item
        if(inventory.size() > 0){
          if(num == 119){
            equipment[inventory[0]->type.c_str()] = inventory[0];
            inventory.erase(inventory.begin()+0);
            toString();
            return;
          }
          //drop an item
          else if(num == 100){
            dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
            dun[getY(enemies[0])][getX(enemies[0])].item = inventory[0]->symbol;
            dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[0]->index;
            inventory.erase(inventory.begin()+0);
            toString();
            return;
          }
          //delete an item
          else if(num == 120){
            items.erase(items.begin()+inventory[0]->index);
            inventory.erase(inventory.begin()+0);
            toString();
            return;
          }
          //inspect an item
          else if(num == 73){
            clear();
            move(1,0);
            printw("%s\n\n", inventory[0]->description.c_str());
            printw("Press esc to return.\n");
            refresh();
            int m = getch();
            while(1){
              if(m == 27){
                toString();
                return;
              }
            }
          }
        }

        break;
      case 49:
      //1
      if(inventory.size() > 1) {
        if(num == 119){
          equipment[inventory[1]->type.c_str()] = inventory[1];
          inventory.erase(inventory.begin()+1);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[1]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[1]->index;
          inventory.erase(inventory.begin()+1);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[1]->index);
          inventory.erase(inventory.begin()+1);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[1]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 50:
      //2
      if(inventory.size() > 2) {
        if(num == 119){
          equipment[inventory[2]->type.c_str()] = inventory[2];
          inventory.erase(inventory.begin()+2);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[2]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[2]->index;
          inventory.erase(inventory.begin()+2);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[2]->index);
          inventory.erase(inventory.begin()+2);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[2]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 51:
      //3
      if(inventory.size() > 3) {
        if(num == 119){
          equipment[inventory[3]->type.c_str()] = inventory[3];
          inventory.erase(inventory.begin()+3);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[3]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[3]->index;
          inventory.erase(inventory.begin()+3);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[3]->index);
          inventory.erase(inventory.begin()+3);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[3]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 52:
      //4
      if(inventory.size() > 4) {
        if(num == 119){
          equipment[inventory[4]->type.c_str()] = inventory[4];
          inventory.erase(inventory.begin()+4);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[4]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[4]->index;
          inventory.erase(inventory.begin()+4);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[4]->index);
          inventory.erase(inventory.begin()+4);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[4]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 53:
      //5
      if(inventory.size() > 5) {
        if(num == 119){
          equipment[inventory[5]->type.c_str()] = inventory[5];
          inventory.erase(inventory.begin()+5);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[5]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[5]->index;
          inventory.erase(inventory.begin()+5);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[5]->index);
          inventory.erase(inventory.begin()+5);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[5]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 54:
      //6
      if(inventory.size() > 6) {
        if(num == 119){
          equipment[inventory[6]->type.c_str()] = inventory[6];
          inventory.erase(inventory.begin()+6);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[6]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[6]->index;
          inventory.erase(inventory.begin()+6);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[6]->index);
          inventory.erase(inventory.begin()+6);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[6]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 55:
      //7
      if(inventory.size() > 7) {
        if(num == 119){
          equipment[inventory[7]->type.c_str()] = inventory[7];
          inventory.erase(inventory.begin()+7);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[7]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[7]->index;
          inventory.erase(inventory.begin()+7);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[7]->index);
          inventory.erase(inventory.begin()+7);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[7]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 56:
      //8
      if(inventory.size() > 8) {
        if(num == 119 && inventory.size() > 1){
          equipment[inventory[8]->type.c_str()] = inventory[8];
          inventory.erase(inventory.begin()+8);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[8]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[8]->index;
          inventory.erase(inventory.begin()+8);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[8]->index);
          inventory.erase(inventory.begin()+8);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[8]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 57:
      //9
      if(inventory.size() > 9) {
        if(num == 119){
          equipment[inventory[9]->type.c_str()] = inventory[9];
          inventory.erase(inventory.begin()+9);
          toString();
          return;
        }
        else if(num == 100){
          dun[getY(enemies[0])][getX(enemies[0])].hasItem = 1;
          dun[getY(enemies[0])][getX(enemies[0])].item = inventory[9]->symbol;
          dun[getY(enemies[0])][getX(enemies[0])].itemIndex = inventory[9]->index;
          inventory.erase(inventory.begin()+9);
          toString();
          return;
        }
        else if(num == 120){
          items.erase(items.begin()+inventory[9]->index);
          inventory.erase(inventory.begin()+9);
          toString();
          return;
        }
        else if(num == 73){
          clear();
          move(1,0);
          printw("%s\n\n", inventory[9]->description.c_str());
          printw("Press esc to return.\n");
          refresh();
          int m = getch();
          while(1){
            if(m == 27){
              toString();
              return;
            }
          }
        }
      }
        break;
      case 27:
      //esc
        toString();
        return;
        break;
    }
  }

}

void displayEquipment(int num){
  int i, j;
  for(i = 0; i < 14; i++){
    move(4+i, 20);
    for(j = 0; j < 40; j++){
      if(i == 0 || i == 13 || j == 0 || j == 39){
        printw("*");
      }
      else{
        printw(" ");
      }
    }
    //printw("\n");
  }
  move(4,35);
  printw("EQUIPMENT");
  int c = 0;
  for(auto& x: equipment){
    move(5+c,21);
    if(equipment[x.first] == NULL){
      printw("Slot %c: %s", c+97, "NULL");
    }
    else{
      printw("Slot %c: %s", c+97, x.second->name.c_str());
    }
    c++;
  }
  refresh();
  int a = getch();
  switch (a) {
    case 97:
    //a
    if(equipment["AMULET"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["AMULET"]);
      equipment["AMULET"] = NULL;
    }
    break;
    case 98:
    //b
    if(equipment["ARMOR"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["ARMOR"]);
      equipment["ARMOR"] = NULL;
    }
    break;
    case 99:
    //c
    if(equipment["BOOTS"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["BOOTS"]);
      equipment["BOOTS"] = NULL;
    }
    break;
    case 100:
    //d
    if(equipment["CLOAK"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["CLOAK"]);
      equipment["CLOAK"] = NULL;
    }
    break;
    case 101:
    //e
    if(equipment["GLOVES"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["GLOVES"]);
      equipment["GLOVES"] = NULL;
    }
    break;
    case 102:
    //f
    if(equipment["HELMET"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["HELMET"]);
      equipment["HELMET"] = NULL;
    }
    break;
    case 103:
    //g
    if(equipment["LIGHT"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["LIGHT"]);
      equipment["LIGHT"] = NULL;
    }
    break;
    case 104:
    //h
    if(equipment["OFFHAND"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["OFFHAND"]);
      equipment["OFFHAND"] = NULL;
    }
    break;
    case 105:
    //i
    if(equipment["RANGED"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["RANGED"]);
      equipment["RANGED"] = NULL;
    }
    break;
    case 106:
    //j
    if(equipment["RING-L"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["RING-L"]);
      equipment["RING-L"] = NULL;
    }
    break;
    case 107:
    //k
    if(equipment["RING-R"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["RING-R"]);
      equipment["RING-R"] = NULL;
    }
    break;
    case 108:
    //l
    if(equipment["WEAPON"] != NULL && inventory.size() < 10){
      inventory.push_back(equipment["WEAPON"]);
      equipment["WEAPON"] = NULL;
    }
    break;
  }
  if(a == 27){
    toString();
    return;
  }
}

int makeMove(int y, int x, int num) {
  int canMove = 1;
  if (getAbilities(enemies[num]) & NPC_IFTUN) {
    if (dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness != 255) {
      if (dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness == 0) {
        if (dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '.' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '#' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != ' ' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '<' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '>') {
          canMove = checkCollision(num, getY(enemies[num])+y, getX(enemies[num])+x);
        }
        else{
          dun[getY(enemies[num])+y][getX(enemies[num])+x].type = getRep(enemies[num]);
        }
        if(canMove){
          if (dun[getY(enemies[num])][getX(enemies[num])].ifRoom == 0) {
            //not a room
            dun[getY(enemies[num])][getX(enemies[num])].type = '#';
          }
          else if (dun[getY(enemies[num])][getX(enemies[num])].isStair > 0) {
            if(dun[getY(enemies[num])][getX(enemies[num])].isStair == 1){
              dun[getY(enemies[num])][getX(enemies[num])].type = '>';
            }
            else {
              dun[getY(enemies[num])][getX(enemies[num])].type = '<';
            }
          }
          else {
            //is a room
            dun[getY(enemies[num])][getX(enemies[num])].type = '.';
          }
          setPoint(enemies[num], getX(enemies[num]) + x, getY(enemies[num]) + y);
        }

        //enemies[num].point.y += y;
        //enemies[num].point.x += x;

      }
      else {
        if(dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness < 85) {
          //set to 0
          dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness = 0;
        }
        else {
          // subtract 85 from hardness
          dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness -= 85;
        }
      }
    }
    return 1;
  }
  else {
    if (dun[getY(enemies[num])+y][getX(enemies[num])+x].hardness == 0) {
      //can move
      if (dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '.' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '#' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != ' ' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '<' && dun[getY(enemies[num])+y][getX(enemies[num])+x].type != '>') {
        canMove = checkCollision(num, getY(enemies[num])+y, getX(enemies[num])+x);
      }
      else{
        dun[getY(enemies[num])+y][getX(enemies[num])+x].type = getRep(enemies[num]);
      }
      if(canMove){
        if (dun[getY(enemies[num])][getX(enemies[num])].ifRoom == 0) {
          //not a room
          dun[getY(enemies[num])][getX(enemies[num])].type = '#';
        }
        else if (dun[getY(enemies[num])][getX(enemies[num])].isStair > 0) {
          if(dun[getY(enemies[num])][getX(enemies[num])].isStair == 1){
            dun[getY(enemies[num])][getX(enemies[num])].type = '>';
          }
          else {
            dun[getY(enemies[num])][getX(enemies[num])].type = '<';
          }
        }
        else {
          //is a room
          dun[getY(enemies[num])][getX(enemies[num])].type = '.';
        }
        setPoint(enemies[num], getX(enemies[num]) + x, getY(enemies[num]) + y);
      }

      return 1;
    }
    else {
      return 0;
    }
  }
}

int generalMove(int num) {
  int vert = getY(enemies[0])- getY(enemies[num]);
  int horz = getX(enemies[0]) - getX(enemies[num]);
  int y = 0;
  int x = 0;
  if (vert < 0){
    y = -1;
  }
  else if (vert > 0) {
    y = 1;
  }
  if (horz < 0){
    x = -1;
  }
  else if (horz > 0) {
    x = 1;
  }

  makeMove(y, x, num);


  return 0;
}

int getDist(int y, int x, int num){
  //printf("dist: %d, y: %d, x: %d\n", distance[enemies[num].point.y+y][enemies[num].point.x+x].distance, y, x);
  return distance[getY(enemies[num])+y][getX(enemies[num])+x].distance;
}

//move with path finding
int smartMove(int num) {
  if (getAbilities(enemies[num]) & NPC_IFTUN) {
    pathFinder(getPoint(enemies[0]), 1);
    int y = -1;
    int x = -1;
    int minimum = getDist(y+1, x+1, num);
    for(int i = -1; i < 2; i++){
      for(int k = -1; k < 2; k++){
        if (i == 0 && k == 0) {
          continue;
        }
        if (getDist(i, k, num) < minimum){
          minimum = getDist(i, k, num);
          y = i;
          x = k;
          //printf("i: %d, k: %d\n", i, k);
        }
      }
    }
    //printf("%d %d\n", y, x);
    makeMove(y, x, num);
    //enemies[num].point.x += x;
    //enemies[num].point.y += y;
  }
  else {
    pathFinder(getPoint(enemies[0]), 0);
    int y = -1;
    int x = -1;
    int minimum = getDist(y+1, x+1, num);
    for(int i = -1; i < 2; i++){
      for(int k = -1; k < 2; k++){
        if (i == 0 && k == 0) {
          continue;
        }
        if (getDist(i, k, num) < minimum){
          minimum = getDist(i, k, num);
          y = i;
          x = k;
          //printf("i: %d, k: %d\n", i, k);
        }
      }
    }
    //printf("%d %d\n", y, x);
    makeMove(y, x, num);
  }


  return 0;
}

int erraticMove(int num) {
  int r = rand() % 2;
  //int r = 0;
  if (r == 0) {
    int vert = (rand() % 3) - 1;
    int horiz = (rand() % 3) - 1;
    while(vert == 0 && horiz == 0) {
      vert = (rand() % 3) - 1;
      horiz = (rand() % 3) - 1;
    }
    makeMove(vert, horiz, num);

    return 1;
  }
  else {
    //move off other characteristics
    return 0;
  }
}

//check if a given enemy is in the same room as the player.
int checkRoom(int num){
  if (dun[getY(enemies[0])][getX(enemies[0])].ifRoom == 0 || dun[getY(enemies[num])][getX(enemies[num])].ifRoom == 0) {
    //character or enemy is not in a room so return 0
    return 0;
  }
  int pRoom = -1;
  int eRoom = -2;
  for(int i = 0; i < roomNum; i++){
    if (getX(enemies[0]) >= dRooms[i].x && getX(enemies[0]) < (dRooms[i].x + dRooms[i].rWidth)) {
      if (getY(enemies[0]) >= dRooms[i].y && getY(enemies[0]) < (dRooms[i].y + dRooms[i].rHeight)) {
        pRoom = i;
      }
    }
    if (getX(enemies[num]) >= dRooms[i].x && getX(enemies[num]) < (dRooms[i].x + dRooms[i].rWidth)) {
      if (getY(enemies[num]) >= dRooms[i].y && getY(enemies[num]) < (dRooms[i].y + dRooms[i].rHeight)) {
        eRoom = i;
      }
    }
  }
  if(eRoom == pRoom) {
    //printf("\nsame\n");
    //enemies[num].see = 1;
    setSee(enemies[num], 1);
    return 1;
  }
  return 0;
}

int getMove() {
  int found = 0;
  // int g = 1;
  // int r = 1;
  while (!found){
    int moves = getch();
    switch(moves) {
      case 55:
      case 121:
        //up left
        if(makeMove(-1, -1, 0)){
          found = 1;
        }
        break;
      case 56:
      case 107:
        //up
        if(makeMove(-1, 0, 0)){
          found = 1;
        }
        break;
      case 57:
      case 117:
        //up right
        if(makeMove(-1, 1, 0)){
          found = 1;
        }
        break;
      case 52:
      case 104:
        //left
        if(makeMove(0, -1, 0)){
          found = 1;
        }
        break;
      case 54:
      case 108:
        //right
        if(makeMove(0, 1, 0)){
          found = 1;
        }
        break;
      case 49:
      case 98:
        //down left
        if(makeMove(1, -1, 0)){
          found = 1;
        }
        break;
      case 50:
      case 106:
        //down
        if(makeMove(1, 0, 0)){
          found = 1;
        }
        break;
      case 51:
      case 110:
        //down right
        if(makeMove(1, 1, 0)){
          found = 1;
        }
        break;
      case 32:
        //spacebar skip turn
        found = 1;
        break;
      case 109:
        //list monsters, m
        showMonsters();
        toString();
       break;
      case 60:
        //works with <
        //up stairs
        if (dun[getY(enemies[0])][getX(enemies[0])].isStair == 2){
          getNew();
          found = 1;
        }
        break;
      case 62:
        //works with >
        //down stairs
        if (dun[getY(enemies[0])][getX(enemies[0])].isStair == 1){
          getNew();
          found = 1;
        }
        break;
      case 83:
        //Save and quit
        return 1;
        break;
      case 119:
        //wear an item
        displayInventory(moves);
        break;
      case 116:
        //take off an item
        displayEquipment(moves);
        break;
      case 100:
        //drop an item
        displayInventory(moves);
        break;
      case 120:
        //delete an item from the game
        displayInventory(moves);
        break;
      case 105:
        //list pc inventory
        displayInventory(moves);
        break;
      case 101:
        //list pc equipment
        displayEquipment(moves);
        break;
      case 73:
        //inspect an item
        displayInventory(moves);
        break;
    }
  }
  return 0;
}

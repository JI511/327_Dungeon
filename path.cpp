#include "util.h"


char array[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void initPath(Point_t p);

int32_t compare(const void *key, const void *with) {
  //void pointers, can be anything
  return ((dist_t *) key)->distance - ((dist_t *) with)->distance;

}

void printMap() {
  for (int h = 0; h < 21; h++) {
    for (int w = 0; w < 80; w++) {
      if (distance[h][w].distance < 10) {
        printf("%d", distance[h][w].distance);
      }
      else if (distance[h][w].distance >= 10 && distance[h][w].distance < 36){
        printf("%c", array[distance[h][w].distance - 10]);
      }
      else if (distance[h][w].distance >= 36 && distance[h][w].distance < 62) {
        printf("%c", array[distance[h][w].distance - 36] - 32);
      }
      else {
        printf("%c", dun[h][w].type);
      }
      //printf("%d ", dun[h][w].hardness);
    }
    printf("\n");
  }
}

void checkNeighbors(heap_t *h, dist_t dis, int y, int x, int tunnel) {
  //printf("check neigh\n");
  if (y >= 21 || y < 0 || x >= 80 || x < 0) {
    return;
  }
  int alt = dis.distance + 1;
  // printf("y%d x%d\n", y, x);
  // printf("dis distance %d\n", dis.distance);
  // printf("hard %d\n", dun[y][x].hardness);
  //adjust distance based off wall hardness
  if (tunnel == 1) {
    if (dun[y][x].hardness == 0){
    }
    else if(dun[y][x].hardness >= 1 && dun[y][x].hardness <= 84) {
      alt += 1;
    }
    else if (dun[y][x].hardness >= 85 && dun[y][x].hardness <= 170) {
      alt += 2;
    }
    else if (dun[y][x].hardness >= 171 && dun[y][x].hardness <= 254) {
      alt += 3;
    }
    else {
      alt += 255;
    }
  }
  else {
    //if it isnt zero, dont go this way! (non tunneling)
    if (dun[y][x].hardness != 0) {
      alt += 255;
    }
  }

  if (alt < distance[y][x].distance) {
    //found shorter path
    //printf("update dist\n");
    distance[y][x].distance = alt;
    heap_decrease_key_no_replace(h, distance[y][x].hn);
  }


}
//point p is the location of the @ symbol
void pathFinder(Point_t p, int isTun) {
  //printf("Inside path.c file\n");
  initPath(p);

  heap_t myHeap;
  heap_init(&myHeap, compare, NULL);

  for (int i = 0; i < 21; i++){
    for (int j = 0; j < 80; j++) {
      distance[i][j].hn = heap_insert(&myHeap, &distance[i][j]);
    }
  }
  //printf("test 1\n");
  dist_t *d;
  //while heap is not empty
  while ((d = (dist_t *) heap_remove_min(&myHeap))) {
    //printf("test inside\n");
    //check neighbors method so everything doesnt look so messy, or repetitive
    //top row
    checkNeighbors(&myHeap, *d, d->point.y+1, d->point.x-1, isTun);
    checkNeighbors(&myHeap, *d, d->point.y+1, d->point.x, isTun);
    checkNeighbors(&myHeap, *d, d->point.y+1, d->point.x+1, isTun);
    //middle row
    checkNeighbors(&myHeap, *d, d->point.y, d->point.x-1, isTun);
    checkNeighbors(&myHeap, *d, d->point.y, d->point.x+1, isTun);
    //bottum row
    checkNeighbors(&myHeap, *d, d->point.y-1, d->point.x-1, isTun);
    checkNeighbors(&myHeap, *d, d->point.y-1, d->point.x, isTun);
    checkNeighbors(&myHeap, *d, d->point.y-1, d->point.x+1, isTun);
    //all 8 nieghbors checked now
  }
  //printMap();
  heap_delete(&myHeap);
}

void initPath(Point_t p) {

  for(int i = 0; i < 21; i ++) {
    for(int j = 0; j < 80; j++) {
      //printf("%d %d\n", i, j);
      distance[i][j].distance = 255;
      distance[i][j].point = (Point_t) {j, i};
    }
  }
  distance[p.y][p.x].distance = 0;
}

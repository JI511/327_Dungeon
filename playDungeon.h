#ifndef PLAYDUNGEON_H
# define PLAYDUNGEON_H

# ifdef __cplusplus
extern "C" {
# endif


int erraticMove(int num);
int generalMove(int num);
int smartMove(int num);
int getDist(int y, int x, int num);
int makeMove(int y, int x, int num);
int getMove();
void showMonsters();


# ifdef __cplusplus
}
# endif

#endif

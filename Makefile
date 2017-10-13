all: dungeon

dungeon: character.cpp heap.c dungeon.cpp monsterParse.cpp playDungeon.cpp path.cpp dice.cpp descriptions.cpp item.cpp
	gcc -Wall -Werror heap.c -c
	g++ -g -std=c++11 -Wall -Werror character.cpp dungeon.cpp monsterParse.cpp path.cpp playDungeon.cpp dice.cpp descriptions.cpp item.cpp -c
	g++ -g -Wall -Werror -lncurses character.o dungeon.o monsterParse.o playDungeon.o path.o dice.o descriptions.o item.o heap.o -o dungeon

clean:
	 rm -f dungeon
	 rm -rf dungeon.dSYM
	 rm -f character.o
	 rm -f dungeon.o
	 rm -f heap.o
	 rm -f path.o
	 rm -f playDungeon.o
	 rm -f monsterParse.o
	 rm -f dice.o
	 rm -f descriptions.o
	 rm -f item.o

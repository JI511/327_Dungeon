// #include "util.h"
// #include "character.h"
// #include <cstring>
// #include <cstdlib>
// #include <cstdio>
// #include <iostream>
// #include <istream>
// #include <fstream>
// #include <sstream>
// #include <string>
//
// void printTraits(npc *n);
//
//
// int parseMon(){
//   int number = 1;
//   std::ifstream ifs;
//   char *path = getenv("HOME");
//   std::string path1(path);
//   std::string temp;
//   ifs.open(path1, std::ifstream::in);
//   std::string s1("RLG327 MONSTER DESCRIPTION 1");
//   std::getline(ifs, temp);
//   if(s1.compare(temp) != 0){
//     //printw("test\n");
//     ifs.close();
//     //return 0;
//   }
//   //read in BEGIN MONSTER, if not present, keep going until it is found or the file ends
//   //look for all of the subsets within the monster, if any are missing, end
//   //make sure the monster ends with END, if not the monster isnt valid
//   //continue this process again until file is empty
//   while(std::getline(ifs, temp)){
//
//     bool name = false;
//     bool symb = false;
//     bool color = false;
//     bool desc = false;
//     bool speed = false;
//     bool dam = false;
//     bool hp = false;
//     bool abil = false;
//     int count = 0;
//     int r = rand() % sizeof(dRooms);
//       while (r==playerRoom){
//         r = rand() % sizeof(dRooms);
//       }
//     int x = (rand() % dRooms[r].rWidth) + dRooms[r].x;
//     int y = (rand() % dRooms[r].rHeight) + dRooms[r].y;
//     npc *n = new npc(x,y,number);
//
//     if(temp.compare("BEGIN MONSTER") == 0) {
//       for(int i = 0; i < 8; i++){
//         ifs >> temp;
//         if (temp.compare("NAME") == 0){
//           if(std::getline(ifs, temp) && !name){
//             n->name = temp;
//             name = true;
//             count++;
//           }
//           else{
//             break;
//           }
//         }
//         else if(temp.compare("SYMB") == 0){
//           if(std::getline(ifs, temp) && !symb){
//             std::string b = temp.substr(1);
//             n->rep = *b.c_str();
//             symb = true;
//             count++;
//           }
//           else{
//             break;
//           }
//         }
//         else if(temp.compare("COLOR") == 0){
//           if(std::getline(ifs, temp) && !color){
//             n->color = temp;
//             color = true;
//             count++;
//           }
//           else{
//             break;
//           }
//         }
//         else if(temp.compare("DESC") == 0){
//           if(!desc){
//             std::string descrip("");
//             while(ifs >> temp){
//               //usleep(50000);
//               if(temp.compare(".") == 0){
//                 break;
//               }
//               descrip.append(temp + " ");
//               //printw("%s ", temp.c_str());
//               //refresh();
//             }
//             //printw("\n");
//             n->description = descrip;
//             desc = true;
//             count++;
//           }
//           else{
//             break;
//           }
//         }
//         else if(temp.compare("SPEED") == 0){
//           int a, b, c;
//           if(std::getline(ifs, temp, '+') && !speed){
//             a = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp, 'd')){
//             b = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp)){
//             c = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           //printw("%d %d %d\n", a, b, c);
//           n->spd = dice(a, b, c);
//           speed = true;
//           count++;
//         }
//         else if(temp.compare("DAM") == 0 && !dam){
//           int a, b, c;
//           if(std::getline(ifs, temp, '+') && !dam){
//             a = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp, 'd')){
//             b = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp)){
//             c = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           //printw("%d %d %d\n", a, b, c);
//           n->dam = dice(a, b, c);
//           dam = true;
//           count++;
//         }
//         else if(temp.compare("HP") == 0 && !hp){
//           int a, b, c;
//           if(std::getline(ifs, temp, '+') && !hp){
//             a = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp, 'd')){
//             b = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           if(std::getline(ifs, temp)){
//             c = std::stoi(temp);
//           }
//           else{
//             break;
//           }
//           //printw("%d %d %d\n", a, b, c);
//           n->hp = dice(a,b,c);
//           hp = true;
//           count++;
//         }
//         else if(temp.compare("ABIL") == 0 && !abil){
//           //printw("TESTICLE\n");
//           if(std::getline(ifs, temp) && !abil){
//             //printf("%s\n", temp.c_str());
//             std::string k = temp.substr(1);
//             int8_t abilities = 0;
//             std::string token;
//             std::istringstream stream(k);
//             while(std::getline(stream, token, ' ')){
//               //printf("%s\n", token.c_str());
//               if(token.compare("SMART") == 0){
//                 //printw("SMART ");
//                 abilities = abilities | 1;
//               }
//               else if(token.compare("PASS") == 0){
//                 //printw("PASS ");
//                 abilities = abilities | 1 * 16;
//               }
//               else if(token.compare("TELE") == 0){
//                 //printw("TELE ");
//                 abilities = abilities | 1 * 2;
//               }
//               else if(token.compare("TUNNEL") == 0){
//                 //printw("TUNNEL ");
//                 abilities = abilities | 1 * 4;
//               }
//               else if(token.compare("ERRATIC") == 0){
//                 //printw("ERRATIC ");
//                 abilities = abilities | 1 * 8;
//               }
//               else{
//                 break;
//               }
//
//             }
//             //printf("%d\n", abilities);
//             n->abilities = abilities;
//
//             abil = true;
//             count++;
//           }
//           //printw("%s ", temp.c_str());
//
//           // refresh();
//           // ifs.close();
//           // return 0;
//         }
//         else {
//           break;
//         }
//       // refresh();
//       // ifs.close();
//       // return 0;
//       }
//       if(count == 8){
//         if (ifs >> temp){
//           if(temp.compare("END") == 0){
//             //successful monster
//             //printTraits(n);
//             enemies.push_back((enemy_t *) n);
//             monsterCount = number;
//             number++;
//
//           }
//         }
//       }
//       else{
//         delete n;
//       }
//
//     }
//
//   }
//   //printw("%s\n", temp.c_str());
//   //refresh();
//
//   ifs.close();
//   return 1;
// }
//
// void printTraits(npc *n){
//   // printf("Name:%s\n", n->name.c_str());
//   // printf("Symbol: %c\n", n->rep);
//   // printf("Color:%s\n", n->color.c_str());
//   // printf("Description: %s\n", n->description.c_str());
//   // printf("Speed: %d base %d dice %d sides\n", n->spd.base, n->spd.dice, n->spd.sides);
//   // printf("Damage: %d base %d dice %d sides\n", n->dam.base, n->dam.dice, n->dam.sides);
//   // printf("Health: %d base %d dice %d sides\n", n->hp.base, n->hp.dice, n->hp.sides);
//   // printf("Abilities: ");
//   // if (n->abilities & NPC_INTEL){
//   //   printf("SMART ");
//   // }
//   // if (n->abilities & NPC_TELEP){
//   //   printf("TELE ");
//   // }
//   // if (n->abilities & NPC_IFTUN){
//   //   printf("TUNNEL ");
//   // }
//   // if (n->abilities & NPC_ERRAT){
//   //   printf("ERRATIC ");
//   // }
//   // if (n->abilities & NPC_PASS){
//   //   printf("PASS ");
//   // }
//   // printf("\n\n");
//   //refresh();
// }
//
//
//
//
// //

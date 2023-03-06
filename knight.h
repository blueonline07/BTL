#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void combat(int &event,int &HP,int &level,int &remedy, int &maidenkiss, int i,int &isTiny, int &isFrog,int &currentLevel);
void increseLevel(int x, int &level);
bool isPrime(int n);
int pow10(int n);
int mushMario(int &HP,int &level, int &phoenixdown);
int mushFibo(int &HP);
void mushGhost(int &HP,int event,string pack);
void meet_asclepius(int &remedy, int &maidenkiss, int &phoenixdown,string pack);
void meet_merlin(int &HP,string pack);
void string2int(string s,int a[],int &number_of_events);
#endif // __KNIGHT_H__

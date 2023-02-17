#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
void combat(int &event,int &HP,int &level,int &remedy,int &maidenkiss,int &phoenixdown,int &rescue,int i);
void increseLevel(int x, int &level);
void tiny(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
#endif // __KNIGHT_H__

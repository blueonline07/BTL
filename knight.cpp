#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
void increseLevel(int x, int &level){
    if(level<10){
        level = level + x;
    }
    if(level >= 10){
        level = 10;
    }
}
void tiny(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    if(remedy>0){
        remedy--;
        return;
    }
    else {
        if(HP <5)
        {
            HP = 1;
        }
        else
        {
            HP = HP /5;
        }
    }

}
void combat(int &event,int &HP,int &level,int &remedy,int &maidenkiss,int &phoenixdown,int &rescue, int i){
    int levelO,b,damage;
    float baseDamage[5]={1,1.5,4.5,7.5,9.5};
    b = i%10;
    levelO = i>6?(b>5?b:5):b;
    cout<<levelO<<endl;
    if(level > levelO)
    {
        if(event <6){
            increseLevel(1,level);
        }
        else {
            if(event==6 || event ==7){
                increseLevel(2,level);
            }
        }
    }
    else
    {
        if(level < levelO)
        {
            damage = baseDamage[event-1]*levelO*10;
            HP = HP - damage;
            if(event==6){
                tiny(HP,level,remedy,maidenkiss,phoenixdown,rescue);
            }
        }
    }
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    //string s,s_stats,s_events,files;
    rescue = -1;
    int event,i;

    ifstream MyFile(file_input);

    while(rescue!=1){
        MyFile>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
        int MaxHP = HP;
        while(MyFile>>event){
            i++;
            if(event==0){
                rescue=1;
                break;
            }
            else {
                if(event<6){
                    combat(event,HP,level,remedy,maidenkiss,phoenixdown,rescue,i);

                }
                if(event == 6){
                    combat(event,HP,level,remedy,maidenkiss,phoenixdown,rescue,i);

                }
            }
            display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
            if(HP<=0){
                if(phoenixdown<=0){
                    rescue=0;
                }
                else{
                    phoenixdown--;
                    HP = MaxHP;
                }
            }
        }
    }
    cout<<"You win";

}

#include "knight.h"
int number_of_events,isTiny=-1,isFrog=-1,currentLevel;
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}
int pow10(int n)
{
    int expo =1 ;
    for(int i=1; i<=n; i++)
    {
        expo*=10;
    }
    return expo;
}
void string2int(string s,int a[])
{
    int i=0,e=0,tmp;
    for(int i=0; i<s.size(); i++)
    {
        a[i]=0;
    }
    for(int k=s.size()-1; k>=0; k--)
    {
        if(s[k]!=' ')
        {
            a[i]=a[i]+ (s[k]-48)*pow10(e);
            e++;
        }
        else
        {
            e=0;
            i++;
        }
    }
    number_of_events = i+1;
    for(int k=0,j=number_of_events-1; k<number_of_events/2; k++)
    {
        tmp = a[j];
        a[j]=a[k];
        a[k]=tmp;
        j--;
    }
}
void increseLevel(int x, int &level)
{
    if(level<10)
    {
        level = level + x;
    }
    if(level >= 10)
    {
        level = 10;
    }
}
void combat(int &event,int &HP,int &level,int &remedy,int &maidenkiss,int &phoenixdown,int &rescue, int i)
{
    int levelO,b,damage;
    float baseDamage[5]= {1,1.5,4.5,7.5,9.5};
    b = i%10;
    levelO = i>6?(b>5?b:5):b;
    //cout<<level<<" "<<levelO<<endl;
    if(level > levelO)
    {
        if(event <6)
        {
            increseLevel(1,level);
        }
        else
        {
            if(event==6 || event ==7)
            {
                if(isTiny==0 && isFrog==0)
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
            if(event==6)
            {
                if(isTiny<=0&&isFrog<=0)
                {

                        isTiny = 3;
                        if(HP<5)
                        {
                            HP = 1;
                        }
                        else
                            HP = HP/5;


                }
            }
            if(event==7)
            {
                if(isTiny<=0 && isFrog<=0)
                {

                        isFrog=3;
                        currentLevel = level;
                        level =1;
                }
            }
        }
    }
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue)
{
    //string s,s_stats,s_events,files;
    rescue = -1;
    int event[100];
    int khoangtrang=0;
    string sukien,filee;
    ifstream MyFile(file_input);

    MyFile>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
    int MaxHP = HP;
    int k=0;
    while(getline(MyFile,sukien))
    {
        k++;
        if(k==2)
            break;
    }
    string2int(sukien,event);
    while(getline(MyFile,filee))
    {
        k++;
        //cout<<filee;
        if(k==3)
            break;
    }
    for(int i=0; i<number_of_events; i++)
    {
        if(event[i]==0)
        {
            rescue=1;
        }
        if(rescue ==0 || rescue==1)
            break;
        isTiny--;
        isFrog--;
        cout<<isFrog<<endl;
        if(event[i]<=7)
        {
            combat(event[i],HP,level,remedy,maidenkiss,phoenixdown,rescue,i+1);
        }
        if(HP<=0)
        {
            if(phoenixdown<=0)
            {
                rescue=0;
            }
            else
            {
                phoenixdown--;
                HP = MaxHP;
                isFrog = -1;
                isTiny = -1;
            }
        }
        if(remedy>0){
            remedy--;
            isTiny=0;
        }
        if(maidenkiss>0){
            maidenkiss--;
            isFrog=0;
        }
        if(isFrog==0)
        {
            level = currentLevel;
        }
        if(isTiny==0)
        {
            HP = HP*5;
            if(HP>MaxHP)
            {
                HP = MaxHP;
            }
        }
        if(i==number_of_events-1 && HP>0)
            rescue=1;
        display(HP,level,remedy,maidenkiss,phoenixdown,rescue);

    }
    if(rescue==0)
    {
        cout<<"Game Over";
    }
    else
    {
        if(rescue==1)
            cout<<"You win";
    }

}

#include "knight.h"
int number_of_events,isTiny=-1,isFrog=-1,currentLevel,MaxHP;
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue)
{
    cout << "HP=" << HP
         << ", level=" << level
         << ", remedy=" << remedy
         << ", maidenkiss=" << maidenkiss
         << ", phoenixdown=" << phoenixdown
         << ", rescue=" << rescue << endl;
}
bool isPrime(int n){
    bool p[1600];
    for(int i=0; i<=1600; i++){
        p[i]=1;
    }
    p[1]=0;
    p[0]=0;
    for(int i=2; i<=400; i++){
        if(p[i]==1)
            for(int j=i*i; j<=1600; j+=i){
                p[j]=0;
            }
    }
    return p[n];
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
int mushMario(int &HP,int &level, int &phoenixdown){
    int s1,j=99;
    int n1 = ((level +phoenixdown)%5+1)*3;
    while(n1--){
        s1+=j;
        j-=2;
    }
    HP = HP + (s1%100);
    while(!isPrime(HP)){
        HP++;
    }
    if(HP>MaxHP){
        HP= MaxHP;
    }
    return HP;
}
int mushFibo(int &HP){
    bool isfibo[1000];
    int f[17];
    f[1]=1;
    f[2]=1;
    for(int i=3 ;i<=16; i++){
        f[i]=f[i-1]+f[i-2];
    }
    for(int i=1; i<=12; i++){
        isfibo[f[i]]=true;
    }
    if(HP>1){
        while(!isfibo[HP]){
            HP--;
        }
    }
    return HP;
}
void mushGhost(int &HP,int event,string pack){
    ifstream file(pack);//nho doi ten lai theo file tc1_input
    int type[100];
    int n2,arr[100];
    int cnt=0;
    file>>n2;
    while(file>>arr[cnt]){
        cnt++;
        if(file.peek()==',')
            file.ignore();
    }
    cnt=0;
    while(event!=13){
        type[cnt]=event%10;
        event/=10;
        cnt++;
    }
    while(cnt--){
        if(type[cnt]==1){
            int maxx=0, minn = 1e9,maxi,mini;
            for(int i=0; i<n2; i++){
                if(arr[i]<minn){
                    minn = arr[i];
                    mini = i;
                }
                if(arr[i]> maxx){
                    maxx = arr[i];
                    maxi=i;
                }
            }
            HP = HP - (maxi + mini);
        }
        if(type[cnt]==2){

        }
    }

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
    if((level+ x )<=10)
    {
        level = level + x;
    }
    if((level + x) > 10)
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
    MaxHP = HP;
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
        if(event[i]<=7)
        {
            combat(event[i],HP,level,remedy,maidenkiss,phoenixdown,rescue,i+1);
        }
        else{
            if(event[i]  ==11){
                HP = mushMario(HP,level,phoenixdown);
            }
            if(event[i]==12){
                HP = mushFibo(HP);
            }
            if(event[i]>99){
                mushGhost(HP,event[i],"tc1_mush_ghost");
            }
        }
        ///thu cai switch
        /*switch(event[i]){
            case 11:
                mushMario(HP,level,phoenixdown);
                break;
            case 12:
                mushFibo(HP);
                break;
            case 13:


        }*/

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
        }
        if(HP>MaxHP){
            HP = MaxHP;
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

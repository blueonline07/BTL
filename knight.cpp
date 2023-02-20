#include "knight.h"
int number_of_events,isTiny=-1,isFrog=-1,currentLevel,MaxHP;
int r1,c1,potion[1000][1000]; //asclepius
int n9; //merlin
bool had_met_asclepius=false;
bool had_met_merlin = false;
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
    ifstream file(pack);
    int type[100];
    int n2,arr[100],x[100];
    int cnt=0;
    file>>n2;
    while(file>>arr[cnt]){
        cnt++;
        if(file.peek()==',')
            file.ignore();
    }
    for(int i=0; i<n2;i++){
        if(arr[i]<0){
            x[i]=-arr[i];
        }
        x[i]=(17*arr[i]+9)%257;
    }
    cnt=0;
    while(event!=13){
        type[cnt]=event%10;
        event/=10;
        cnt++;
    }
    int maxx,minn;
    while(cnt--){
        if(type[cnt]==1){
            maxx=0, minn = 1e9;
            int maxi,mini;
            for(int i=0; i<n2; i++){
                if(arr[i]<minn){
                    mini = i;
                }
                if(arr[i]> maxx){
                    maxi=i;
                }
            }
            HP = HP - (maxi + mini);
        }
        if(type[cnt]==2){    ///chua code dinh nui

        }
        if(type[cnt]==3){
            maxx=0,minn=1e9;
            int maxi2,mini2;
            for(int i=0; i<n2; i++){
                if(x[i]<minn){
                    mini2=i;
                }
                if(x[i]>maxx){
                    maxi2=i;
                }
            }
            HP = HP - (maxi2+mini2);
        }
        if(type[cnt]==4){
            maxx=0,minn=1e9;
            int max2_3x,max2_3i;
            for(int i=0; i<3; i++){
                if(x[i]<minn){
                    minn = x[i];
                }
                if(x[i]>maxx){
                    maxx=x[i];
                }
            }
            bool exist_2nd=false;
            for(int i=0; i<3; i++){
                if(x[i]!=minn && x[i]!=maxx){
                    max2_3x = x[i];
                    max2_3i = i;
                    exist_2nd = true;
                }
            }
            if(!exist_2nd){
                max2_3x = -5;
                max2_3i = -7;
            }
            HP = HP - (max2_3i + max2_3x);
        }
    }

}
void meet_asclepius(int &remedy, int &maidenkiss, int &phoenixdown,string pack){
    if(had_met_asclepius)
        return;

    ifstream file(pack);
    file>>r1>>c1;
    for(int i=0; i<r1; i++){
        for(int j=0; j<c1; j++){
            file>>potion[i][j];
        }
    }

    int limit=3;
    for(int i=0; i<r1; i++){
        limit = 3;
        for(int j=0; j<c1; j++){
            if(limit){
                if(potion[i][j]==16){
                    remedy++;
                    limit--;
                }
                if(potion[i][j]==17){
                    maidenkiss++;
                    limit--;
                }
                if(potion[i][j]==18){
                    phoenixdown++;
                    limit--;
                }
            }
        }
    }
    had_met_asclepius=true;
}
void meet_merlin(int &HP,string pack){
    if(had_met_merlin)
        return;
    ifstream file(pack);
    string merlin_items;
    file>>n9;
    while(n9--){
        file>>merlin_items;
        if(merlin_items=="Merlin" || merlin_items=="merlin"){
            HP = HP +3;
        }
        else
            HP = HP + 2;
    }
    had_met_merlin = true;
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
    string s_event,files,mush_ghost,asclepius,merlin;
    ifstream MyFile(file_input);

    MyFile>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
    MaxHP = HP;
    int k=0;
    while(getline(MyFile,s_event))
    {
        k++;
        if(k==2)
            break;
    }
    string2int(s_event,event);
    MyFile>>files;
    k=0;
    int n=0;
    while(files[n]!='\0'){
        n++;
    }
    for(int i=0; i<n; i++){
        if(files[i]==','){
            k++;
            continue;
        }
        if(k==0)
            asclepius += files[i];
        if(k==1)
            merlin +=files[i];
        if(k==2)
            mush_ghost +=files[i];
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
                mushGhost(HP,event[i],mush_ghost);
            }
            if(event[i] ==15){
                remedy ++;
            }
            if(event[i]==16){
                maidenkiss++;
            }
            if(event[i]==17){
                phoenixdown++;
            }
            if(event[i]==18){
                meet_merlin(HP,merlin);
            }
            if(event[i]==19){
                meet_asclepius(remedy,maidenkiss,phoenixdown,asclepius);
            }
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
        if(remedy>0 && isTiny >0){
            remedy--;
            isTiny=0;
        }
        if(maidenkiss>0 && isFrog>0){
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
    ///nho xoa may cai duoi
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

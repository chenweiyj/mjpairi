#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>

using namespace std;

const int MAXS=34;
const int rt[13]={0,8,9,17,18,26,27,28,29,30,31,32,33};
const char c[4]={'m','p','s','z'};

int tct;
int minx;

void analy(string st, int p1[MAXS])
{
    int i,j,t;
    int tmp[9];
    
    memset(p1,0,MAXS*sizeof(int));
    memset(tmp,0,sizeof(tmp));
    for (i=0;i<st.size();i++)
    {
        if (st[i]=='0') st[i]='5';
        if (st[i]>='1'&&st[i]<='9')
        {
            tmp[st[i]-'1']++;
            continue;
        }
        if (st[i]=='m') t=0;
        if (st[i]=='p') t=1;
        if (st[i]=='s') t=2;
        if (st[i]=='z') t=3;
        for (j=0;j<9;j++)
        {
            p1[t*9+j]+=tmp[j];
        }
        memset(tmp,0,sizeof(tmp));
    }
}
    

bool check(int a[MAXS], int rem)
{
    int i;
    
    if (rem==0) return true;
    for (i=0;i<34;i++)
    {
        if (a[i]>=3)
        {
            a[i]-=3;
            if (check(a,rem-1)) {a[i]+=3;return true;}
            a[i]+=3;
        }
        if (i>=27) continue;
        if (i%9==0||i%9==8) continue;
        if (a[i]==0||a[i-1]==0||a[i+1]==0) continue;
        a[i]--;a[i-1]--;a[i+1]--;
        if (check(a,rem-1)) {a[i]++;a[i-1]++;a[i+1]++;return true;}
        a[i]++;a[i-1]++;a[i+1]++;
    }
    return false;
}

bool agari(int a[MAXS])
{
    int i,ct;
    bool t;
    bool bl1,bl2;
    
    //7-pairs
    ct=0;
    for (i=0;i<34;i++)
    {
        if (a[i]>=2) ct++;
    }
    if (ct>=7) return true;
    //gokushi
    bl1=true;bl2=false;
    for (i=0;i<13;i++)
    {
        if (a[rt[i]]==0)
        {
            bl1=false;
            break;
        }
        if (a[rt[i]]>1)
        {
            bl2=true;
        }
    }
    if (bl1&&bl2) return true;
    //general shape
    for (i=0;i<34;i++)
    {
        if (a[i]<2) continue;
        a[i]-=2;
        t=check(a,4);
        if (t) {a[i]+=2;return true;}
        a[i]+=2;
    }
    return false;
}

void shanten(int a[MAXS], int lay)
{
    int i,t;
    
    if (lay>=minx) return;
    if (agari(a)) minx=lay;
    
    tct++;
    //if (tct%10000==0) cout<<tct<<endl;
    
    for (i=0;i<34;i++)
    {
        if (a[i]==4) continue;
        
        if (i>=27||i%9==0||i%9==8)
        {
            if (a[i]==0) continue;
        } else {
            if (a[i]==0&&a[i-1]==0&&a[i+1]==0) continue;
        }
        
        a[i]++;
        shanten(a,lay+1);
        a[i]--;
    }
}

int main()
{
    string st;
    
    int i,j,tot,nst;
    int p1[MAXS];
    
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    
    cin>>st;
    analy(st,p1);
    if (agari(p1)) {cout<<"Agari!"<<endl;return 0;}
    tct=0;
    minx=6;
    shanten(p1,0);
    if (minx==1) cout<<"Tenpai."<<endl; else cout<<minx-1<<" shanten."<<endl;
    nst=minx;
    for (i=0;i<34;i++)
    {
        if (p1[i]==0) continue;
        p1[i]--;
        minx=nst+1;
        shanten(p1,0);
        cout<<"Play "<<i%9+1<<c[i/9]<<":";
        if (minx>nst) {
            p1[i]++;
            cout<<" Don't."<<endl;
            continue;
        }
        tot=0;
        for (j=0;j<34;j++)
        {
            if (i==j) continue;
            if (p1[j]==4) continue;
        
            p1[j]++;
            minx=nst;
            shanten(p1,0);
            if (minx<nst) {cout<<" "<<j%9+1<<c[j/9];tot+=5-p1[j];};
            p1[j]--;
        }
        p1[i]++;
        cout<<" | "<<tot<<" total."<<endl;
    }
            
    cout<<"Done!"<<endl;
    while (true);
            
    return 0;
}

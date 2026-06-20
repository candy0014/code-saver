#include <bits/stdc++.h>
using namespace std;

pair<int,int> navigate(int cu, vector<int> cv){
    int d=cv.size();
    if(cu==3){
        for(int i=0;i<d;i++) if(cv[i]==0) return make_pair(1,i);
        for(int i=d-1;i>=0;i--) if(cv[i]==2) return make_pair(1,i);
        return make_pair(-1,-1);
    }
    int flag=-1;
    for(int i=0;i<d;i++) if(cv[i]==3){flag=i;break;}
    if(flag!=-1){
        int cnt=0;
        for(auto x:cv) cnt+=(x==2);
        if(cnt>1) return make_pair(2,flag);
        return make_pair(0,flag);
    }
    for(int i=0;i<d;i++) if(cv[i]==0) return make_pair(2,i);
    int cnt=0;
    for(auto x:cv) cnt+=(x==2);
    for(int i=0;i<d;i++) if(cv[i]==2) return make_pair((cnt==1)?1:3,i);
    return make_pair(-1,-1);
}
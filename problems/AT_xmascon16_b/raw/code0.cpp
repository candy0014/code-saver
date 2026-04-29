#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> >res[2][6];
vector<pair<int,int> >solve(int n){
    if(n==2){
        return {{1,2},{0,1},{0,2},{0,0},{2,2},{3,2},{1,1}};
    }
    res[0][0]=res[1][0]={{0,1},{1,0},{1,1}};
    for(int i=1;i<=n/2;i++){
        int d=1<<i;
        for(auto [x,y]:res[1][i-1]) res[0][i].emplace_back(x+d,y+d);
        res[0][i].emplace_back(d+d/2-1,d);
        for(auto [x,y]:res[0][i-1]) res[0][i].emplace_back(x+d,d-y-1);
        res[0][i].emplace_back(d,d-1);
        res[1][i]=res[0][i];
        vector<pair<int,int> >tmp;
        for(auto [x,y]:res[1][i-1]) tmp.emplace_back(x,y+d);
        tmp.emplace_back(d/2-1,d);
        for(auto [x,y]:res[0][i-1]) tmp.emplace_back(x,y);
        for(auto [x,y]:tmp) res[0][i].emplace_back(x,y),res[1][i].emplace_back(d-x-1,y);
    }
    return res[0][n/2];
}
int main(){
    vector<pair<int,int> >res=solve(11);
    for(auto [x,y]:res) cout<<x<<" "<<y<<"\n";
    return 0;
}
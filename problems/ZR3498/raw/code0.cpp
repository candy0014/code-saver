#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int st[500005],top;
void solve(){
    cin>>n>>s,s=" "+s;
    if(n&1){cout<<"-1\n";return;}
    int la=0,laj=0;
    top=0;
    for(int i=1;i<=n;i++){
        for(int j=s[i]-'0'+1;j<=4;j++){
            if(j==3){
                if(n-i>=top+1){la=i,laj=j;break;}
            }
            else if(top&&j-1==st[top]){
                if(n-i>=top-1){la=i,laj=j;break;}
            }
        }
        if(s[i]=='1'||s[i]=='3') st[++top]=s[i]-'0';
        else{
            if(!top||s[i]-'1'!=st[top]) break;
            top--;
        }
    }
    if(!la){cout<<"-1\n";return;}
    top=0,s[la]=laj+'0';
    for(int i=1;i<=n;i++){
        if(i>la){
            for(int j=1;j<=4;j++){
                if(j==1||j==3){
                    if(n-i>=top+1){s[i]=j+'0';break;}
                }
                else if(top&&j-1==st[top]){
                    s[i]=j+'0';break;
                }
            }
        }
        if(s[i]=='1'||s[i]=='3') st[++top]=s[i]-'0';
        else{
            if(!top||s[i]-'1'!=st[top]) break;
            top--;
        }
    }
    for(int i=1;i<=n;i++) cout<<s[i];cout<<"\n";
}
int main(){
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int ID,Ca;cin>>ID>>Ca;while(Ca--)solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int n,q,id[30005];
mt19937 rd(time(0));
char ask(int x){
	cout<<"? "<<x<<endl;
	char g;cin>>g;return g;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) id[i]=i;
	shuffle(id+1,id+n+1,rd);
	int mi=id[1],flag=1;ask(id[1]);
	for(int i=2;i<=n;i++){
		if(ask(id[i])=='>'){
			if(flag) mi=id[i];
			else{
				if(ask(mi)=='<') mi=id[i];
				else flag=1;
			}
		}
		else flag=0;
	}
	cout<<"! "<<mi<<endl;
	return 0;
}
